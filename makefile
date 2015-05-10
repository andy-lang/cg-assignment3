PLATFORM := $(shell uname)
CC = g++

PROJ_LIBS = libs
LIB_FLAG = -I

ifneq (, $(findstring CYGWIN, $(PLATFORM)))
    GL_LIBS = -lopengl32 -lglut32
	EXT = .exe
    DEFS =-DWIN32
endif

ifneq (, $(findstring Linux, $(PLATFORM)))
    GL_LIBS = -lGL -lglut -lGLEW 
	GL_LIBS += -L/usr/lib/nvidia-304 # Needed for some linux drivers
	EXT = 
    DEFS =
endif

ifneq (, $(findstring Darwin, $(PLATFORM)))
    DEFS   = -DMacOSX -D__APPLE__ -m32 -arch x86_64    
    GL_LIBS = -framework GLUT -framework OpenGL -framework CoreFoundation -lGLEW
	EXT = 
endif


all: assign3$(EXT)

assign3: main.o Object.o Shader.o tiny_obj_loader.o
	$(CC) $(DEFS) -o assign3 main.o Object.o tiny_obj_loader.o Shader.o $(GL_LIBS)

main.o: main.cpp Shader.o tiny_obj_loader.o Object.o
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c main.cpp

Shader.o: Shader.cpp Shader.hpp
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Shader.cpp

Object.o: Object.cpp Object.hpp
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Object.cpp

tiny_obj_loader.o: tiny_obj_loader.h tiny_obj_loader.cc
	$(CC) $(DEFS) -c tiny_obj_loader.cc

clean:
	rm -f *.o assign3$(EXT)
