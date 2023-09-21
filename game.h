#ifndef GAME_H
#define GAME_H
#include "entity.h"
#include "carriage.h"
#include "ball.h"
#include "bonus.h"

const int32_t WINDOW_WIDTH = 500;
const int32_t WINDOW_HEIGHT = 700;

class game
{
public:
	static game* G;
	int currentTime;
	game() {
		G = this;
		currentTime = 0;
		entity::BonusesDuration();
		windowSize = { WINDOW_WIDTH, WINDOW_HEIGHT };
		create_field();
		ball* ballT = new ball();
		carriage* carriageT = new carriage();
	}
	PAIR getWindowSize();
	void initGame(int argc, char** argv);
	void mechanic();


private:
	PAIR windowSize;
	void initGlutFunctions();
	void create_field();
};
#endif


