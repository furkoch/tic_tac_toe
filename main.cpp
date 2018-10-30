#include <iostream>
#include "GameConfig.h"
#include "GameEngine.h"

int main(int argc, char** argv) 
{
	std::cout<<"Welcome to Tic Tac Toe game"<<std::endl;
	
	std::string ans;

	do{
		GameConfig gameConfig;
		if(!gameConfig.readConfigFile(argv[1])){
			return -1;
		}
		GameEngine engine(gameConfig);
		engine.run();

		std::cout<<"Would you like to play again(Y/N)?"<<std::endl;		
		std::cin>>ans;
				
	}while(ans=="Y" || ans=="y");

	return 0;
}