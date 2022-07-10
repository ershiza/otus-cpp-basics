#include "parse_arg.h"
#include "game.h"
#include "io_score.h"

#include <iostream>
#include <string>

int parseArguments(int argc, char** argv)
{
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
		if (arg1_value == "-max" && isValidMaxArg(argc, argv))
        {
			int parameter_value = std::stoi(argv[2]);
			std::cout << "The '-max' value = " << parameter_value << std::endl;

			playGame(parameter_value);
			
        }
        else if (arg1_value == "-level" && isValidLevelArg(argc, argv))
        {
			int parameter_value = std::stoi(argv[2]);
			std::cout << "The '-level' value = " << parameter_value << std::endl;

			playGame(maxValueByLevel.find(parameter_value)->second);
        }
        else if (arg1_value == "-table" && isValidTableArg(argc, argv))
        {
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

bool isValidMaxArg(int argc, char** argv)
{
	std::cout << "-max argument was detected!" << std::endl;

	if (argc < 3) {
		std::cout << "The argument '-max' requires some value!" << std::endl;
		return false;
	}

	int parameter_value = std::stoi(argv[2]);

	if (parameter_value < 1)
	{
		std::cout << "The argument '-max' must be a positive number!" << std::endl;
		return false;
	}

	return true;
}

bool isValidLevelArg(int argc, char** argv)
{
	std::cout << "-level argument was detected!" << std::endl;

	if (argc < 3) {
		std::cout << "The argument '-level' requires value = 1, 2, 3!" << std::endl;
		return false;
	}

	int parameter_value = std::stoi(argv[2]);

	if (parameter_value != 1 && parameter_value != 2 && parameter_value != 3)
	{
		std::cout << "The argument '-level' requires value = 1, 2, 3!" << std::endl;
		return false;
	}

	return true;
}

bool isValidTableArg(int argc, char** argv)
{
	std::cout << "-table argument was detected!" << std::endl;

	if (argc > 2) {
		std::cout << "The argument '-table' should not contain additional parameters!" << std::endl;
		return false;
	}

	return true;
}