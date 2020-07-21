CC = g++

SRC = ./src/**.cpp

LINKER = -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -lmingw32 -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32 -lgdi32

WARNING_FLAGS = -Wall -Wno-comment
RELEASE_FLAGS = -O3
DEBUG_FLAGS = -g

OUTPUT = ./build/output.exe

release:
	$(CC) $(SRC) $(LINKER) $(WARNING_FLAGS) $(RELEASE_FLAGS) -o $(OUTPUT)

debug:
	$(CC) $(SRC) $(LINKER) $(WARNING_FLAGS) $(DEBUG_FLAGS) -o $(OUTPUT)