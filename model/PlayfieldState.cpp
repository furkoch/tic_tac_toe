#include "PlayfieldState.h"

PlayfieldState::PlayfieldState(int boardSize) 
{
	gameState = GameState::PLAYING;
	stateMatrix.resize(boardSize, std::vector<char>(boardSize, '\0'));
	// Initialize
	for(int i=0; i<boardSize*boardSize; i++) {
		stateMatrix[i/boardSize][i%boardSize] = '\0';
	}
}

void PlayfieldState::setGameState(GameState gs)
{
	gameState = gs;
}

void PlayfieldState::update(int row, int col, char val) 
{
	stateMatrix[row][col] = val;
}

PlayfieldState::~PlayfieldState()
{
	stateMatrix.clear();
}
