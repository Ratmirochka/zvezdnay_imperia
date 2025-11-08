# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

# Пути и файлы
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = star_empire

# Правило по умолчанию — сборка
all: $(TARGET)

# Линковка
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Правило компиляции .cpp → .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(SRC_DIR)/*.o *.o $(TARGET)

# Полная пересборка
rebuild: clean all
