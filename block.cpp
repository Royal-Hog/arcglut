#include "block.h"
#include "ball.h"
#include "ballProtectB.h"
#include "ballSpeedB.h"
#include "ballStickingB.h"
#include "carriageSizeB.h"
#include "game.h"
#include <GL/freeglut.h>

std::set<block*> block::BlockList;
PAIR block::size;
void block::BallCollide()
{
	block* Removing = NULL;
	for (block* Block : BlockList)
	{
		if (Removing)
		{
			delete Removing;
			Removing = NULL;
		}
		PAIR Contacting = contact(Block, ball::ExitingBall);
		if (Contacting != EMPTY_PAIR)
		{
			if (Block->hp != absolut)
				Block->hp--;
			ball::ExitingBall->Bounce(Contacting, Block);
			ball::ExitingBall->move();
		}
		if (Block->hp <= 0)
			Removing = Block;
	}
	if (Removing) {
		delete Removing;
		Removing = NULL;
	}
}
void block::BlockCollide()
{
	for (block* OuterBlock : BlockList) {
		for (block* InnerBlock : BlockList) {
			PAIR Contacting = contact(OuterBlock, InnerBlock);

			if (OuterBlock != InnerBlock && Contacting != EMPTY_PAIR) {
				OuterBlock->position.x -= OuterBlock->speed.x;
				OuterBlock->position.y -= OuterBlock->speed.y;
				InnerBlock->position.x -= InnerBlock->speed.x;
				InnerBlock->position.y -= InnerBlock->speed.y;
				OuterBlock->setSpeed({ OuterBlock->getSpeed().x * (-1), 0.0 });
				InnerBlock->setSpeed({ OuterBlock->getSpeed().x * (-1), 0.0 });
				while (Contacting.x > 0) {
					OuterBlock->move();
					InnerBlock->move();
					Contacting = contact(OuterBlock, InnerBlock);
					std::cout << Contacting.x << '\n';
				}

			}
		}
	}
}

void block::BlockMoving() {
	for (auto Block : BlockList) {
		Block->move();
	}
}
void block::setSize(PAIR s) {
	size = s;
}

PAIR block::getSize() {
	return size;
}

void block::DrawBlock() {
	glBegin(GL_QUADS);
	glColor3f(1.0 * hp / absolut * 1.0f, 1.0 * hp / absolut * 0.6f, 1.0 * hp / absolut * 0.8f);
	glVertex2f(position.x - size.x / 2, position.y - size.y / 2);
	glVertex2f(position.x - size.x / 2, position.y + size.y / 2);
	glVertex2f(position.x + size.x / 2, position.y + size.y / 2);
	glVertex2f(position.x + size.x / 2, position.y - size.y / 2);
	glEnd();
}

void block::DrawCurrentBlocks() {
	for (auto u : BlockList) {
		u->DrawBlock();
	}
}

void block::CreateBonus() {
	int chance = takeChance(4);
	bonus* p;
	switch (chance) {
	case 0:
		p = new ballProtectB(position);
		break;
	case 1:
		p = new ballSpeedB(position);
		break;
	case 2:
		p = new ballStickingB(position);
		break;
	case 3:
		p = new carriageSizeB(position);
		break;
	}
}

int32_t block::getHP() {
	return hp;
}