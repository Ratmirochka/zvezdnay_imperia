#include "include/Game.h"
#include <iostream>
#include <locale>

#ifdef _WIN32
    #include <windows.h>
#endif

int main() {
    // Устанавливаем русскую локаль для вывода
    setlocale(LC_ALL, "ru_RU.UTF-8");

#ifdef _WIN32
    // Для Windows-консоли: переключить кодировку на UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "Добро пожаловать в консольную игру 'Звёздные Империи'!\n";
    Game game;
    game.run();

    return 0;
}