#ifndef PLAYER
#define PLAYER

#include <iostream>

class Player {

public:
	Player(char pChar);
	virtual ~Player();
	inline char getChar()& {return character;}

protected:
	char character;

};

#endif