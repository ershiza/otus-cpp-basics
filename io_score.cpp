#include "io_score.h"

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <map>

bool writeScore(std::string user_name, int attempts_count)
{
	std::ofstream out_file{scores_filename, std::ios_base::app};
	if (!out_file.is_open()) {
		std::cout << "Failed to open file for write: " << scores_filename << "!" << std::endl;
		return false;
	}

	out_file << user_name << ' ';
	out_file << attempts_count;
	out_file << std::endl;

	std::cout << "Запись результа в файл " << scores_filename << ": " << user_name << ' ' << attempts_count << std::endl;

	return true;
}

bool writeHighScore(std::string user_name, int attempts_count)
{
	std::fstream out_file{high_scores_filename, std::ios_base::in};
	if (!out_file.is_open()) {
		std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
		return false;
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
				return true;
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
			return false;
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
			return false;
		}

		out_file << user_name << ' ';
		out_file << attempts_count;
		out_file << std::endl;
	
		out_file.close();

		std::cout << "Запись нового игрока в файл " << high_scores_filename << std::endl;
	}

	return true;
}

bool readScoreTable()
{
	std::ifstream in_file{scores_filename};
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << scores_filename << "!" << std::endl;
		return false;
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

    return true;
}

bool readHighScoreTable()
{
	std::ifstream in_file{high_scores_filename};
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
		return false;
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

	return true;
}