CC = g++ -std=c++17

SRC = ./src/**.cpp

LINKER_WINDOWS = -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -lmingw32 -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32 -lgdi32
LINKER_LINUX = -static-libgcc -static-libstdc++ -lstdc++ -lpthread -lSDL2main -lSDL2 -lGL -lGLEW

WARNING_FLAGS = -Wall -Wno-comment
RELEASE_FLAGS = -O3 -mfpmath=sse
DEBUG_FLAGS = -g -D_DEBUG

OUTPUT_DIR = ./build
OUTPUT = $(OUTPUT_DIR)/output.exe

# Windows

release-windows:
	$(CC) $(SRC) $(LINKER_WINDOWS) $(WARNING_FLAGS) $(RELEASE_FLAGS) -o $(OUTPUT)
release-windows-run: release-windows run

debug-windows:
	$(CC) $(SRC) $(LINKER_WINDOWS) $(WARNING_FLAGS) $(DEBUG_FLAGS) -o $(OUTPUT)
debug-windows-run: debug-windows run

# Linux

release-linux:
	$(CC) $(SRC) $(LINKER_LINUX) $(WARNING_FLAGS) $(RELEASE_FLAGS) -o $(OUTPUT)
release-linux-run: release-linux run

debug-linux:
	$(CC) $(SRC) $(LINKER_LINUX) $(WARNING_FLAGS) $(DEBUG_FLAGS) -o $(OUTPUT)
debug-linux-run: debug-linux run

run:
	cd $(OUTPUT_DIR) && output.exe