#include "game.h"
#include "io_score.h"

#include <iostream>
#include <ctime>
#include <string>

void playGame(int max_value)
{
	std::srand(std::time(nullptr));

	const int target_value = std::rand() % max_value;

	std::cout << "Максимальное значение загаданного числа: "  << max_value << ". (СПОЙЛЕР) Загаданное число: " << target_value << std::endl;

	std::cout << std::endl << "Игра \"Угадай число\"." << std::endl;
    std::cout << "Привет! Введите своё имя: ";
	std ::string user_name;
	std::cin >> user_name;
 
	int current_value = 0;
    int attempts_count = 0;
	bool not_win = true;

	std::cout << "Введите число:" << std::endl;
	do {
		attempts_count++;

        while (!(std::cin >> current_value))
        {
            std::cin.clear();
            while (std::cin.get() != '\n')
                continue;
            std::cout << "Нужно ввести число: ";
        }

	} while(notEqual(current_value, target_value));

    std::cout << "Количество попыток: " << attempts_count << std::endl << std::endl;

	writeScore(user_name, attempts_count);
	writeHighScore(user_name, attempts_count);

	readScoreTable();

    return;
}

bool notEqual(int current_value, int target_value)
{
	if (current_value > target_value) {
		std::cout << "Загаданное число < " << current_value << std::endl;
		return true;
	}
	else if (current_value < target_value) {
		std::cout << "Загаданное число > " << current_value << std::endl;
		return true;
	}
	else {
		std::cout << "Вы угадали! Было загадано число: " <<  target_value << std::endl;
		return false;
	}
}