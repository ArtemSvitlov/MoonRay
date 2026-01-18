# --- Переменные ---
PROJECT_NAME = MoonRay
CC = x86_64-w64-mingw32-g++
CFLAGS = -I./include -Wall
LDFLAGS = -L./libs

# Библиотеки
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -luser32 -lshell32

# Ищем исходники в корне src и в src/core
SRC = $(wildcard src/*.cpp) $(wildcard src/core/*.cpp)

# Имя выходного файла
EXE = MoonRay.exe

# --- Цели ---

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(EXE)

run: $(EXE)
	./$(EXE)



# 4. Очистка
.PHONY: clean
clean:
	@rm -f $(EXE)
	@echo [CLEAN] Executable removed.