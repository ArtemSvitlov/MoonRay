# --- Настройки ---
PROJECT_NAME = MoonRay
CC = x86_64-w64-mingw32-g++
EXE = MoonRay.exe

# Добавляем путь к Lua (согласно твоей структуре)
# Добавил -I./include/components на всякий случай
CFLAGS = -I./include -I./include/lua -I./include/components -Wall -DNO_FONT_AWESOME -O2
LDFLAGS = -L./libs

# Библиотеки (добавляем lua53)
LIBS = -lraylib -llua53 -lopengl32 -lgdi32 -lwinmm -luser32 -lshell32

# Поиск исходников
SRC = $(wildcard src/*.cpp) \
      $(wildcard src/core/*.cpp) \
      $(wildcard include/Imgui/*.cpp) \
      $(wildcard src/imgui_impl/*.cpp)

# Превращаем список .cpp в список .o
OBJ = $(SRC:.cpp=.o)

# --- Цели ---

all: $(EXE)

# Линковка: зависит от всех .o файлов
$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LIBS) -o $(EXE)
	@echo [LINK] Success!

# Компиляция каждого файла: теперь изменения в любом файле будут подхвачены
# Чтобы Makefile видел изменения в .h, можно добавить зависимость от заголовков
%.o: %.cpp
	$(CC) -c $< $(CFLAGS) -o $@
	@echo [CC] $<

run: $(EXE)
	./$(EXE)

.PHONY: clean
clean:
	@rm -f $(EXE) $(OBJ)
	@echo [CLEAN] Executable and objects removed.