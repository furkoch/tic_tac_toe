#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H
#include <string>
#include <iostream>
#include <vector>

class GameConfig
{
public:
	GameConfig(){};
	bool readConfigFile(std::string filename);
	std::vector<unsigned> shuffleMoveOrder();
	GameConfig& operator=(const GameConfig& other);

	inline std::vector<char> getChars() const  {return characters;}
	inline unsigned getBoardSize() const {return boardSize;}

private:
	unsigned boardSize = 3;
	std::vector<char> characters;//Order:Player1, Player2, PlayerAI	
};

#endif