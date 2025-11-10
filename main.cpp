#include "include/Game.h"
#include <iostream>
#include <locale>

#ifdef _WIN32
    #include <windows.h>
#endif

int main() {
    // Устанавливаем русскую локаль для корректного отображения в VS Code/Windows
    setlocale(LC_ALL, "ru_RU.UTF-8");

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "Добро пожаловать в консольную игру 'Звёздные Империи'!\n";

    // Используем Singleton: берём единственный экземпляр и запускаем игру
    Game::instance().run();

    return 0;
}
