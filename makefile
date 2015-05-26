PLATFORM := $(shell uname)
CC = g++

EXTERNAL_FILES = external_files
PROJ_LIBS = libs
LIB_FLAG = -I
SOIL_LIBS = ./$(EXTERNAL_FILES)/soil/lib

ifneq (, $(findstring CYGWIN, $(PLATFORM)))
    GL_LIBS = -lopengl32 -lglut32
	EXT = .exe
    DEFS =-DWIN32
endif

ifneq (, $(findstring Linux, $(PLATFORM)))
    GL_LIBS = -lGL -lglut -lGLEW 
	GL_LIBS += -L/usr/lib/nvidia-304 # Needed for some linux drivers
	EXT = 
    DEFS = -I../glm-0.9.4.0/
endif

ifneq (, $(findstring Darwin, $(PLATFORM)))
    DEFS   = -DMacOSX -D__APPLE__ -m32 -arch x86_64    
    GL_LIBS = -framework GLUT -framework OpenGL -framework CoreFoundation -lGLEW
	EXT = 
endif


all: assign3$(EXT)

assign3: main.o Shape.o Object.o Player.o Shader.o tiny_obj_loader.o Camera.o
	mkdir -p ./$(EXTERNAL_FILES)/soil/projects/makefile/obj
	mkdir -p ./$(EXTERNAL_FILES)/soil/lib
	make -C ./$(EXTERNAL_FILES)/soil/projects/makefile/
	$(CC) $(DEFS) -o assign3 $^ $(GL_LIBS) -L$(SOIL_LIBS) -lSOIL

main.o: main.cpp Player.o Shader.o tiny_obj_loader.o Shape.o Object.o Camera.o $(PROJ_LIBS)/*
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c main.cpp

Shader.o: Shader.cpp Shader.hpp $(PROJ_LIBS)/*
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Shader.cpp

Camera.o: Camera.cpp Camera.hpp $(PROJ_LIBS)/*
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Camera.cpp

Player.o: Player.cpp Player.hpp Object.o $(PROJ_LIBS)/*
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Player.cpp

Object.o: Object.cpp Object.hpp Shape.o $(PROJ_LIBS)/*
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Object.cpp

Shape.o: Shape.cpp Shape.hpp $(PROJ_LIBS)/*
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Shape.cpp

tiny_obj_loader.o: tiny_obj_loader.h tiny_obj_loader.cc $(PROJ_LIBS)/*
	$(CC) $(DEFS) -c tiny_obj_loader.cc

clean:
	rm -f *.o assign3$(EXT)
	make clean -C ./$(EXTERNAL_FILES)/soil/projects/makefile
