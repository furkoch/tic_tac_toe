#include "GameEngine.h"
#include <sstream>

GameEngine::GameEngine(GameConfig gConfig):gameConfig(gConfig)
{	
	int boardSize = gameConfig.getBoardSize();

	field = new Playfield(boardSize);	
	state = new PlayfieldState(boardSize);	
	players.resize(3);
}

GameEngine::~GameEngine()
{
	delete field;
	delete state;
}

void GameEngine::run()
{
	//Create players
	state->setGameState(GameState::PLAYING);
	std::vector<char> characters = gameConfig.getChars();
	for(int i=0; i<players.size(); i++)
		players[i] = new Player(characters[i]);

	//Generate order of move for players
	std::vector<unsigned> moveOrder = gameConfig.shuffleMoveOrder();
	//Print it out
	std::cout<<"Order of move:";
	for(unsigned i=0; i<moveOrder.size(); i++)
		std::cout<<"\t"<<players[moveOrder[i]]->getChar();
	std::cout<<std::endl;

	int p = 0;

	while(state->getGameState()==GameState::PLAYING){
		//Select a player who starts first
		activePlayer = players[moveOrder[p]];
		char playerChar = activePlayer->getChar();
		std::pair<int, int> move;

		if(playerChar==characters[2]) {
			move = makeMoveAI(playerChar);
			std::cout<<"AI moved to "<<move.first<<":"<<move.second<<std::endl;
			if(move.first==-1 && move.second==-1) {
				state->setGameState(GameState::DRAW);
				std::cout<<"Draw game!"<<std::endl;
				return;
			}
		}			
		else
			move = makeMove(playerChar);

		// std::pair<int, int> move = makeMoveAI(playerChar);
		//Update state matrix
		state->update(move.first, move.second, playerChar);
		field->update(move.first, move.second, playerChar);

		field->paint();
		//Check if player won or draw
		if(checkWin(playerChar, move.first, move.second)){
			if(playerChar==characters[0]) {
				state->setGameState(GameState::PLAYER_ONE_WON);
			}else if(playerChar==characters[1]){
				state->setGameState(GameState::PLAYER_TWO_WON);
			}else if(playerChar==characters[2]){ 
				state->setGameState(GameState::PLAYER_AI_WON);
			}
			std::cout<<"Player "<<playerChar<<" won!"<<std::endl;
		} else if(checkDraw()){
			state->setGameState(GameState::DRAW);
			std::cout<<"Draw game!"<<std::endl;
		}

		p = (p==2) ? 0 : p+1;
	}
}

std::pair<int, int> GameEngine::makeMove(char playerChar)
{
	int boardSize = gameConfig.getBoardSize();

	while(1) {

		// std::cout<<"Empty cells: ";
		// for(int i=0; i<boardSize*boardSize; i++) {
		// 	int x = i/boardSize;
		// 	int y = i%boardSize;
		// 	if(state->getStateMatrix()[x][y] == '\0') {
		// 		std::cout<<"("<<x<<","<<y<<") ";
		// 	}
		// }

		std::cout<<std::endl;

		std::cout<< "Player "<<playerChar<<" enter your move in format 3,2: ";
		std::string inStr;
		std::cin>>inStr;
		//split and read
		std::istringstream pos(inStr);

		int i=0;
		std::string charPos;

		try{
			getline(pos,charPos,',');
			int inRow = stoi(charPos);
			getline(pos,charPos,',');
			int inCol = stoi(charPos);

			
			if(inRow>=0 && inRow<boardSize && inCol>=0 && inCol<boardSize) {

				if(state->getStateMatrix()[inRow][inCol]=='\0'){
					return std::pair<int, int>(inRow, inCol);
				}

				std::cout<<"Cell "<<inRow<<":"<<inCol<<" is taken.Choose another cell"<<std::endl;
				
			}else {
				std::cout<<"Numbers should be between 0 and "<<boardSize<<std::endl;
			}
		}catch(...){
			std::cout<<"Unable to convert string into numbers"<<std::endl;
		}
	}
}

std::pair<int, int> GameEngine::makeMoveAI(char playerChar) {
	int boardSize = gameConfig.getBoardSize();

	/*Strategy for AI 
		1. Find a row, col, diag or opposite diag with the maximal number of 
		its elements and other elements are empty.
		2.If such a row, col, diag exists, select a cell from that.
		3.If such a row, col, diag do not exist, select any non empty cell.
	*/

	//Select a row with max playerChar elements
	int rowSelected = -1;
	int colSelected = -1;
	int nPlayerCharsMax = 0;

	for(int i=0; i<boardSize; i++) {
		int emptyCells = 0;
		int nPlayerChars = 0;
		int cs = -1;
		for(int j=0; j<boardSize; j++) {
			if(state->getStateMatrix()[i][j] == '\0'){
				emptyCells++;
				//select last empty cell
				cs = j;
			}else if(state->getStateMatrix()[i][j] == playerChar){
				nPlayerChars++;
			}
		}

		if(nPlayerChars+emptyCells == boardSize) {
			colSelected = cs;
			if((nPlayerChars>=nPlayerCharsMax)) {
				nPlayerCharsMax = nPlayerChars;
				rowSelected = i;
			}
		}
	}

	if(rowSelected!=-1 && colSelected!=-1){
		return std::make_pair(rowSelected, colSelected);
	}
		
	
	//Select a column with max playerChar elements 
	rowSelected = -1;
	colSelected = -1;
	nPlayerCharsMax = 0;

	for(int i=0; i<boardSize; i++) {
		int emptyCells = 0;
		int nPlayerChars = 0;
		//Check for rows
		int rs = -1;
		for(int j=0; j<boardSize; j++) {
			if(state->getStateMatrix()[j][i] == '\0'){
				emptyCells++;
				rs = j;
			}else if(state->getStateMatrix()[j][i] == playerChar){
				nPlayerChars++;				
			}
		}
		if(nPlayerChars+emptyCells == boardSize) {
			rowSelected = rs;
			if(nPlayerChars>=nPlayerCharsMax) {
				nPlayerCharsMax = nPlayerChars;
				colSelected = i;
			}
		}
	}

	if(rowSelected!=-1 && colSelected!=-1){
		return std::make_pair(rowSelected, colSelected);
	}
	//Select a diagonal with max playerChar elements 
	rowSelected = -1;
	colSelected = -1;

	int emptyCells = 0;
	int nPlayerChars = 0;

	for(int i=0; i<boardSize; i++) {
		if(state->getStateMatrix()[i][i] == '\0'){
			emptyCells++;
			rowSelected = i;
		}else if(state->getStateMatrix()[i][i] == playerChar){
			nPlayerChars++;
		}
	}

	colSelected = rowSelected;

	if(colSelected!=-1 && (nPlayerChars+emptyCells == boardSize)){
		return std::make_pair(rowSelected, colSelected);
	}

	//Select an opposite diagonal with max playerChar elements 

	rowSelected = -1;
	colSelected = -1;

	emptyCells = 0;
	nPlayerChars = 0;

	for(int i=0; i<boardSize; i++) {
		if(state->getStateMatrix()[i][i] == '\0'){
			emptyCells++;
			rowSelected = i;
		}else if(state->getStateMatrix()[i][boardSize - i -1] == playerChar){
			nPlayerChars++;
		}
	}

	colSelected = rowSelected;

	if(colSelected!=-1 && (nPlayerChars+emptyCells == boardSize)){
		return std::make_pair(rowSelected, colSelected);
	}

	//Select a first non-empty cell
	for(int i=0; i<boardSize; i++) {
		for(int j=0; j<boardSize; j++) {
			if(state->getStateMatrix()[i][j] == '\0'){
				return std::make_pair(i, j);
			}
		}
	}

	return std::make_pair(-1, -1);
}

bool GameEngine::checkDraw()
{
	int boardSize = gameConfig.getBoardSize();

	for(int i=0; i<boardSize; i++) {
		for(int j=0; j<boardSize; j++) {
			if(state->getStateMatrix()[i][j] == '\0'){
				return false;
			}
		}
	}

	return true;
}

bool GameEngine::checkWin(char playerChar, int row, int col)
{
	int boardSize = gameConfig.getBoardSize();
	int counter = 0;

	//Check current row
	for(int i=0; i<boardSize; i++){
		if(state->getStateMatrix()[row][i] == playerChar) {
			counter++;
		}
	}

	if(counter == boardSize)
		return true;

	//Check current col
	counter = 0;
	for(int i=0; i<boardSize; i++){
		if(state->getStateMatrix()[i][col] == playerChar) {
			counter++;
		}
	}

	if(counter == boardSize)
		return true;

	//Check diagonal
	if (row == col) {
		counter = 0;
		for(int i=0; i<boardSize; i++){
			if(state->getStateMatrix()[counter][counter] == playerChar) {
				counter++;
			}
		}
		
		if(counter == boardSize)
			return true;
	}

	//Check opposite diagonal	
	if (row + col == boardSize-1) {
		counter = 0;

		for(int i=0; i<boardSize; i++){
			if(state->getStateMatrix()[counter][boardSize-counter-1] == playerChar) {
				counter++;
			}
		}
		
		if(counter == boardSize)
			return true;
	}

	return false;
}
