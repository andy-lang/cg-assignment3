PLATFORM := $(shell uname)
CC = g++

EXT_FILES = external_files
PROJ_LIBS = libs
LIB_FLAG = -I
SOIL_LIBS = ./$(EXT_FILES)/soil/lib

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

assign3: main.o Object.o Player.o Shader.o tiny_obj_loader.o Camera.o LevelMap.o Shape.o Light.o Particle.o ParticleGenerator.o
	mkdir -p ./$(EXT_FILES)/soil/projects/makefile/obj
	mkdir -p ./$(EXT_FILES)/soil/lib
	make -C ./$(EXT_FILES)/soil/projects/makefile/
	$(CC) $(DEFS) -o assign3 $^ $(GL_LIBS) -L$(SOIL_LIBS) -lSOIL

main.o: main.cpp Player.o Shader.o tiny_obj_loader.o Shape.o Object.o Camera.o LevelMap.o Light.o Particle.o ParticleGenerator.o
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c main.cpp

ParticleGenerator.o: ParticleGenerator.cpp ParticleGenerator.hpp Particle.o
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c ParticleGenerator.cpp

Particle.o: Particle.cpp Particle.hpp
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Particle.cpp

Shader.o: Shader.cpp Shader.hpp
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Shader.cpp

Light.o: Light.cpp Light.hpp
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Light.cpp

Camera.o: Camera.cpp Camera.hpp
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Camera.cpp

Player.o: Player.cpp Player.hpp Object.o
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Player.cpp

Object.o: Object.cpp Object.hpp Shape.o
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Object.cpp

LevelMap.o: LevelMap.cpp LevelMap.hpp
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c LevelMap.cpp

Shape.o: Shape.cpp Shape.hpp
	$(CC) $(DEFS) $(LIB_FLAG) $(PROJ_LIBS) -c Shape.cpp

tiny_obj_loader.o: $(EXT_FILES)/tiny_obj_loader/tiny_obj_loader.h $(EXT_FILES)/tiny_obj_loader/tiny_obj_loader.cc
	$(CC) $(DEFS) -c $(EXT_FILES)/tiny_obj_loader/tiny_obj_loader.cc

clean:
	rm -f *.o assign3$(EXT) $(EXT_FILES)/tiny_obj_loader/tiny_obj_loader.o
	make clean -C ./$(EXT_FILES)/soil/projects/makefile
