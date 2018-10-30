#include "GameConfig.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>

bool GameConfig::readConfigFile(std::string filename)
{
	std::string line;
	std::ifstream infile(filename);
	bool ret = false;
	int i=0;
	while(std::getline(infile, line)) {
		std::istringstream iss(line);
		if(i==0){
			iss>>boardSize;
			std::cout<<boardSize<<std::endl;
			if(boardSize>10 || boardSize<3) {
				std::cout<<"Board size should be in range [3,10]"<<std::endl;
				return false;
			}
		}else if(i==1) {
			std::string str;
			iss>>str;

			std::string token;
			std::istringstream tokenStream(str);

			while (std::getline(tokenStream, token, ',')) {	
				characters.push_back(token.c_str()[0]);
			}
		}		
		i++;
	}

	if(characters.size()!=3) {
		std::cout<<"3 characters should be given"<<std::endl;
		return false;
	}

	return true;
}

GameConfig& GameConfig::operator=(const GameConfig& other) {

	boardSize = other.getBoardSize();

	for(int i=0; i< 3; i++)
		characters[i] = other.getChars()[i];

	return *this;
}

std::vector<unsigned> GameConfig::shuffleMoveOrder()
{
	std::vector<unsigned> moveOrder = {0, 1, 2};
	unsigned cnt  =  std::chrono::system_clock::now()
				.time_since_epoch()
				.count();
	std::shuffle(std::begin(moveOrder), std::end(moveOrder), std::default_random_engine(cnt));

	return moveOrder;
}