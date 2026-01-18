# Переменные
CC = x86_64-w64-mingw32-g++
CFLAGS = -I./include
LDFLAGS = -L./libs

# Библиотеки для Raylib (Windows MinGW)
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -luser32 -lshell32

SRC = $(wildcard src/core/*.cpp)

EXE = MyLittleEngine.exe

# 1. Цель по умолчанию
all: $(EXE)

# 2. Компиляция
$(EXE): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(EXE)

# 3. Новая команда: запуск
# Символ @ перед командой скрывает саму строку вызова в консоли
run: $(EXE)
	./$(EXE)

# 4. Очистка
.PHONY: clean
clean:
	@if exist $(EXE) del /f /q $(EXE)
	@echo [CLEAN] Executable removed.