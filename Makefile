# Source folder
SRC_DIR = source

# Build folder
BLD_DIR = 

#OBJS specifies which files to compile as part of the project 
OBJS = $(SRC_DIR)/main.cpp $(SRC_DIR)/MainWindow.cpp 
OBJS += $(SRC_DIR)/GameObject.cpp $(SRC_DIR)/SpaceObject.cpp $(SRC_DIR)/Ship.cpp 
OBJS += $(SRC_DIR)/WorldScene.cpp 
OBJS += $(SRC_DIR)/ShipTile.cpp 
OBJS += $(SRC_DIR)/LTexture.cpp $(SRC_DIR)/LTextureAnimation.cpp 
OBJS += $(SRC_DIR)/TextureManager.cpp

#CC specifies which compiler we're using 
CC = g++ 

#INCLUDE_PATHS specifies the additional include paths we'll need 
INCLUDE_PATHS = -ID:\mingw_dev_lib\include\SDL2 

#LIBRARY_PATHS specifies the additional library paths we'll need 
LIBRARY_PATHS = -LD:\mingw_dev_lib\lib 

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
COMPILER_FLAGS = -w 

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = MageSpace

#This is the target that compiles our executable 
all : $(OBJS) 
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)