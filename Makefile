# Source folder
SRC_DIR = source

# Build folder
BLD_DIR = build

#OBJS specifies which files to compile as part of the project 
OBJS = $(SRC_DIR)/main.cpp $(SRC_DIR)/MainWindow.cpp $(SRC_DIR)/GameObject.cpp $(SRC_DIR)/SpaceObject.cpp

#CC specifies which compiler we're using 
CC = g++ 

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
COMPILER_FLAGS = -w 

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = $(BLD_DIR)/main

#This is the target that compiles our executable 
all : $(OBJS) 
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)