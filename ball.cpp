#include "ball.h"
#include "game.h"
#include <GL/freeglut.h>
ball* ball::ExitingBall;

PAIR ball::getSize() {
	return { radius * 2, radius * 2 };
}

void ball::move()
{
	if (sticking)
	{
		PAIR getP = carriage::Carriage->getPosition();
		setPosition({ getP.x,
			getP.y + carriage::Carriage->getSize().y / 2.0 + radius });
		return;
	}
	if (game::G->currentTime - ChangeSpeed < durationOfBonuses)
	{
		position.x += speed.x * 1.5;
		position.y += speed.y * 1.5;
	}
	else {
		position.x += speed.x;
		position.y += speed.y;
	}
	bounceOff();


	if (position.y - radius < 0) {
		if (protection) {
			speed.y *= -1;
			protection = false;
		}
		else {
			delete this;
			Sleep(500);
			exit(EXIT_SUCCESS);
		}
	}
}


void ball::Bounce(PAIR Contacting, entity* EntityWith) {
	if (sticking)
		return;
	position.x -= speed.x;
	position.y -= speed.y;
	double offset = (takeChance(3) - 1);
	double my_pi = cos(0.0);
	if (Contacting.x < Contacting.y)
	{
		double alpha = (this->getPosition().x - EntityWith->getPosition().x) * 120 / EntityWith->getSize().x + offset;
		double velocity_y = FullVelocity * cos(alpha * my_pi / 180);
		double velocity_x = (-1) * FullVelocity * sin(alpha * my_pi / 180);
		this->setSpeed({ velocity_x, velocity_y });
	}
	else
	{
		double alpha = (this->getPosition().y - EntityWith->getPosition().y) * 120 / EntityWith->getSize().y + offset;
		double velocity_y = FullVelocity * sin(alpha * my_pi / 180);
		double velocity_x = (-1) * FullVelocity * cos(alpha * my_pi / 180);
		this->setSpeed({ velocity_x, velocity_y });
	}
	move();
}

void ball::drawBall() {
	double pi = 2 * acos(0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.9f, 0.9f, 0.9f);
	for (size_t i = 0; i < 50; ++i)
		glVertex2f(position.x + radius * cos(2 * pi / 50.0 * i),
			position.y + radius * sin(2 * pi / 50.0 * i));
	glEnd();

	if (protection) {
		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0, 0);
		glVertex2f(0, 10);
		glVertex2f(game::G->getWindowSize().x, 10);
		glVertex2f(game::G->getWindowSize().x, 0);
		glEnd();
	}
}