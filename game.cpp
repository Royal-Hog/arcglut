#include "game.h"
#include "block.h"
#include <ctime>
#include <GL/freeglut.h>

game* game::G;
void game::create_field() {
	for (double x = 0; x < game::windowSize.x; x += 50)
	{
		for (double y = game::windowSize.y; y >= game::windowSize.y / 2; y -= 25)
		{
			int32_t chance = (rand() + time(NULL)) % int((game::windowSize.y - y) / 30 + 1);
			if (chance == 0) block* p = new block({ x + 30.0, y - 15.0 });
		}
	}
}

PAIR game::getWindowSize() {
	return windowSize;
}

game* CurrentInstance;

extern "C"

void game::initGame(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 0);
	glutInitWindowSize(500, 700);
	glutCreateWindow("Арканоид");

	initGlutFunctions();

	glutMainLoop();
}
bool win() {
	bool Victory = true;
	for (block* Block : block::BlockList)
	{
		if (Block->getHP() != absolut)
		{
			Victory = false;
			break;
		}
	}
	return Victory;
}

void game::mechanic() {
	currentTime++;
	if (!ball::ExitingBall && !win()) {
		Sleep(500);
		exit(0);
	}
	block::BlockMoving();
	bonus::BonusMoving();
	ball::ExitingBall->move();
	block::BallCollide();
	block::BlockCollide();
	bonus::CarriageCollide();
	carriage::BallCollide();
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double w = glutGet(GLUT_WINDOW_WIDTH);
	double h = glutGet(GLUT_WINDOW_HEIGHT);
	glOrtho(0, w, 0, h, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	CurrentInstance->mechanic();
	block::DrawCurrentBlocks();
	bonus::DrawBonuses();
	ball::ExitingBall->drawBall();
	carriage::Carriage->DrawCarriage();
	glutSwapBuffers();
	glutPostRedisplay();
}


void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(EXIT_SUCCESS);
	}
	if (key == ' ')
		if (ball::ExitingBall->sticking) ball::ExitingBall->sticking = false;
	if (key == 'd' || key == 'D') carriage::Carriage->RightMoving();
	if (key == 'a' || key == 'A') carriage::Carriage->LeftMoving();
}

void resize(int32_t fiction_width, int32_t fiction_height)
{
	glViewport(0, 0, 500, 700);
}

void game::initGlutFunctions()
{
	CurrentInstance = this;
	::glutDisplayFunc(::renderScene);
	::glutIdleFunc(::renderScene);
	::glutKeyboardFunc(::processNormalKeys);
	::glutReshapeFunc(::resize);
}