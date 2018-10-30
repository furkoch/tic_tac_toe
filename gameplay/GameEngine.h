#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <iostream>
#include <vector>

#include "Playfield.h"
#include "Cell.h"
#include "PlayfieldState.h"
#include "GameConfig.h"
#include "Player.h"

class GameEngine
{
public:
	GameEngine(GameConfig gameConfig);
	~GameEngine();
	void run();
private:
	bool checkDraw();
	bool checkWin(char playerChar, int row, int col);
	std::pair<int, int> makeMove(char playerChar);
	std::pair<int, int> makeMoveAI(char playerChar);
	
	void update(Player player);

	Playfield* field;
	GameConfig gameConfig;
	PlayfieldState* state;
	std::vector<Player*> players; //1st, 2nd and AI player
	Player* activePlayer;
};

#endif