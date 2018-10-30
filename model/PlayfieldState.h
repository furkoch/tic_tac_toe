#ifndef PLAYFIELD_STATE
#define PLAYFIELD_STATE

#include <vector>

enum GameState {PLAYING, PLAYER_ONE_WON, 
				PLAYER_TWO_WON, PLAYER_AI_WON, DRAW};

class PlayfieldState {

public:
	PlayfieldState(int boardSize);
	~PlayfieldState();
	inline const std::vector<std::vector<char>>& getStateMatrix() { return stateMatrix; }
	inline GameState getGameState() & { return gameState; }
	void setGameState(GameState gs);
	void update(int row, int col, char val);
private:
	GameState gameState;
	std::vector<std::vector<char>> stateMatrix;	
};

#endif