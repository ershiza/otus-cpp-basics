#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <map>

#include <cstdlib>
#include <ctime>

const std::string scores_filename = "../scores.txt";
const char* high_scores_filename = "../high_scores.txt";

void playGame(int max_value = 100);
int getMaxValue(int);
bool writeScore(std::string, int);
bool writeHighScore(std::string, int);
bool readScoreTable();
bool readHighScoreTable();

int main(int argc, char** argv) {

    if (argc >= 4) 
    {
        std::cout << "Wrong usage!" << std::endl;
        return -1;
    }
    else if (argc == 1)
    {
		std::cout << "We have only one argument!" << std::endl;
		std::cout << "argv[0] = " << argv[0] << std::endl;

        playGame();
	}
    else
    {
        std::string arg1_value{argv[1]};
		if (arg1_value == "-max")
        {
            std::cout << "-max argument was detected!" << std::endl;

			int parameter_value = 0;
			if (argc < 3) {
				std::cout << "Wrong usage! The argument '-max' requires some value!" << std::endl;
				return -1;
			}

			parameter_value = std::stoi(argv[2]);
			std::cout << "The '-max' value = " << parameter_value << std::endl;

            playGame(parameter_value);
        }
        else if (arg1_value == "-level")
        {
            std::cout << "-level argument was detected!" << std::endl;

			int parameter_value = 0;
			if (argc < 3) {
				std::cout << "Wrong usage! The argument '-level' requires value = 1, 2, 3!" << std::endl;
				return -1;
			}

			parameter_value = std::stoi(argv[2]);

            if (parameter_value != 1 && parameter_value != 2 && parameter_value != 3)
            {
                std::cout << "Wrong usage! The argument '-level' requires value = 1, 2, 3!" << std::endl;
                return -1;
            }
            
			std::cout << "The '-level' value = " << parameter_value << std::endl;

            playGame(getMaxValue(parameter_value));
        }
        else if (arg1_value == "-table")
        {
            std::cout << "-table argument was detected!" << std::endl;

			if (argc > 2) {
				std::cout << "Wrong usage!" << std::endl;
				return -1;
			}
            readHighScoreTable();
        }
        else
        {
            std::cout << "Wrong usage!" << std::endl;
			return -1;
        }
    }

	return 0;
}

int getMaxValue(int level)
{
    switch (level)
    {
        case 1: return 10;
        case 2: return 50;
        case 3: return 100;
        default: return -1;
    }
}

void playGame(int max_value)
{
    if (max_value == -1)
        return;

	std::srand(std::time(nullptr));

	const int target_value = std::rand() % max_value;

	std::cout << "Максимальное значение загаданного числа: "  << max_value << ". (СПОЙЛЕР) Загаданное число: " << target_value << std::endl;

	std::cout << std::endl << "Игра \"Угадай число\"." << std::endl;
    std::cout << "Привет! Введите своё имя: ";
	std::string user_name;
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

		if (current_value > target_value) {
			std::cout << "Загаданное число < " << current_value << std::endl;
		}
		else if (current_value < target_value) {
			std::cout << "Загаданное число > " << current_value << std::endl;
		}
		else {
			std::cout << "Вы угадали! Было загадано число: " <<  target_value << std::endl;
			break;
		}

	} while(true);

    std::cout << "Количество попыток: " << attempts_count << std::endl << std::endl;

	writeScore(user_name, attempts_count);
	writeHighScore(user_name, attempts_count);

	readScoreTable();
    readHighScoreTable();

    return;
}


bool writeScore(std::string user_name, int attempts_count)
{
	std::ofstream out_file{scores_filename, std::ios_base::app};
	if (!out_file.is_open()) {
		std::cout << "Failed to open file for write: " << scores_filename << "!" << std::endl;
		return -1;
	}

	out_file << user_name << ' ';
	out_file << attempts_count;
	out_file << std::endl;

	std::cout << "Запись результа в файл " << scores_filename << ": " << user_name << ' ' << attempts_count << std::endl;

	return 0;
}

bool writeHighScore(std::string user_name, int attempts_count)
{
	std::fstream out_file{high_scores_filename, std::ios_base::in};
	if (!out_file.is_open()) {
		std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
		return -1;
	}

	std::cout << high_scores_filename << ":" << std::endl;

	std::string line;
	std::vector<std::string> buf;
	
	bool do_rewrite = false;

	while (std::getline(out_file, line, '\n'))
	{
		std::string name = line.substr(0, line.find(' '));

		if (name == user_name)
		{
			std::string score = line.substr(line.rfind(' ') + 1);
			std::cout << "Результат из файла: " << name << "\t" << stoi(score) << std::endl;
			std::cout << "Текущий результат:  " << user_name << "\t" << attempts_count << std::endl;

			if (stoi(score) > attempts_count)
			{
				do_rewrite = true;
			}
			else
			{
				std::cout << "Запись в " << high_scores_filename << " не требуется. Результат не стал лучше." << std::endl;

				out_file.close();
				return 0;
			}			
		}
		else 
			buf.push_back(line);
	}

	out_file.close();

	if (do_rewrite)
	{
		const char* buf_filename = "../buffer.txt";
		std::ofstream buf_file(buf_filename, std::ios::out);

		if (!buf_file.is_open()) {
			std::cout << "Failed to open file for write: " << buf_filename << "!" << std::endl;
			return -1;
		}

		for (auto x : buf)
			buf_file << x << std::endl;

		buf_file << user_name << ' ';
		buf_file << attempts_count;
		buf_file << std::endl;

		buf_file.close();

		remove(high_scores_filename);
		rename(buf_filename, high_scores_filename);
		
		std::cout << "Перезапись файла " << high_scores_filename << ". Результат стал лучше." << std::endl;
	}
	else
	{
		out_file.open(high_scores_filename, std::ios_base::out | std::ios_base::app);
		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		out_file << user_name << ' ';
		out_file << attempts_count;
		out_file << std::endl;
	
		out_file.close();

		std::cout << "Запись нового игрока в файл " << high_scores_filename << std::endl;
	}

	return 0;
}

bool readScoreTable()
{
	std::ifstream in_file{scores_filename};
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << scores_filename << "!" << std::endl;
		return -1;
	}

	std::cout << "Лучшие результаты из файла " << scores_filename << ":" << std::endl;

	std::string user_name;
	int high_score = 0;
	std::map <std::string, int> users_score;

	while (true) {
		in_file >> user_name;
		in_file >> high_score;

		in_file.ignore();

		if (users_score.count(user_name))
		{
			if (users_score.find(user_name)->second > high_score)
				users_score.find(user_name)->second = high_score;
		}
		else
			users_score.insert(make_pair(user_name, high_score));

		if (in_file.fail()) {
			break;
		}	
	}

	for (auto x : users_score)
		std::cout << x.first << '\t' << x.second << std::endl;

    return 0;
}

bool readHighScoreTable()
{
	std::ifstream in_file{high_scores_filename};
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
		return -1;
	}

	std::cout << "Лучшие результаты из файла " << high_scores_filename << ":" << std::endl;

	std::string user_name;
	int high_score = 0;
	while (true) {
		in_file >> user_name;
		in_file >> high_score;

		in_file.ignore();
	
		if (in_file.fail()) {
			break;
		}

		std::cout << user_name << '\t' << high_score << std::endl;
	}

	return 0;
}