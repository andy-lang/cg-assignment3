#ifndef LIB_H
#define LIB_H

#define VALS_PER_VERT   3
#define VALS_PER_NORM   3
#define VALS_PER_TEXCOORD 2

#include <iostream>

static unsigned int WINDOW_WIDTH = 640;
static unsigned int WINDOW_HEIGHT = 480;

inline void checkGLError() {
	GLenum err = glGetError();
	std::cout << "checking gl errors..." << std::endl;
	if (err != GL_NO_ERROR) {
	    std::cerr << "GL error: " << std::hex << err << std::endl;
	}
}

#endif
