# --- Переменные ---
PROJECT_NAME = MoonRay
CC = x86_64-w64-mingw32-g++
CFLAGS = -I./include -Wall -DNO_FONT_AWESOME
LDFLAGS = -L./libs

# Библиотеки
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -luser32 -lshell32

# Ищем исходники в корне src, src/core, include/Imgui, src/imgui_impl
SRC = $(wildcard src/*.cpp) $(wildcard src/core/*.cpp) $(wildcard include/Imgui/*.cpp) $(wildcard src/imgui_impl/*.cpp)

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