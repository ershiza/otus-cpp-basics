#include "parse_arg.h"
#include "game.h"
#include "io_score.h"

#include <iostream>
#include <string>

bool parseArguments(int argc, char** argv)
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
		if (arg1_value == "-max")
        {
			parseMax(argc, argv);
        }
        else if (arg1_value == "-level")
        {
			parseLevel(argc, argv);
        }
        else if (arg1_value == "-table")
        {
			parseTable(argc, argv);
        }
        else
        {
            std::cout << "Wrong usage!" << std::endl;
			return -1;
        }
    }

	return 0;
}

bool parseMax(int argc, char** argv)
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

	return 0;
}

bool parseLevel(int argc, char** argv)
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

	playGame(getMaxValue.find(parameter_value)->second);

	return 0;
}

bool parseTable(int argc, char** argv)
{
	std::cout << "-table argument was detected!" << std::endl;

	if (argc > 2) {
		std::cout << "Wrong usage!" << std::endl;
		return -1;
	}

	readHighScoreTable();

	return 0;
}