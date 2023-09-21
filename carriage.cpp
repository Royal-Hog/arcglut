#include "carriage.h"
#include "ball.h"
#include "game.h"
#include <GL/freeglut.h>
carriage* carriage::Carriage;
void carriage::LeftMoving() {
	if (position.x - size.x / 2 > 0)
		position.x -= FullVelocity;
}
void carriage::RightMoving() {
	if (position.x + size.x < game::G->getWindowSize().x + size.x / 2)
		position.x += FullVelocity;
}
PAIR carriage::getSize() {
	if (game::G->currentTime - changeSizeT < durationOfBonuses) {
		return { size.x * 2, size.y * 2 };
	}
	return size;
}
void carriage::BallCollide() {
	PAIR Contacting = contact(ball::ExitingBall, Carriage);
	if (Contacting != EMPTY_PAIR) {
		if (carriage::Carriage->stick) {
			carriage::Carriage->stick = false;
			ball::ExitingBall->sticking = true;
			ball::ExitingBall->setSpeed({ 0.0, 0.0 });
		}
		else {
			ball::ExitingBall->Bounce(Contacting, Carriage);
		}
	}
}
void carriage::DrawCarriage() {
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.4f, 0.0f);
	if (game::G->currentTime - changeSizeT < durationOfBonuses) {
		glVertex2f(position.x - size.x, position.y - size.y / 2);
		glVertex2f(position.x - size.x, position.y + size.y / 2);
		glVertex2f(position.x + size.x, position.y + size.y / 2);
		glVertex2f(position.x + size.x, position.y - size.y / 2);
	}
	else {
		glVertex2f(position.x - size.x / 2, position.y - size.y / 2);
		glVertex2f(position.x - size.x / 2, position.y + size.y / 2);
		glVertex2f(position.x + size.x / 2, position.y + size.y / 2);
		glVertex2f(position.x + size.x / 2, position.y - size.y / 2);
	}

	glEnd();
}