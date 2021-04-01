#include "Obstacles.h"


Obstacles::Obstacles()
{
	rect_.x = SCREEN_WIDTH / 3;
	rect_.y = 0;
	rect_.w = WIDTH_OBSTACLE;
	rect_.h = HEIGHT_OBSTACLE;
	x_val = 0;
	y_val = 0;
}

Obstacles::~Obstacles()
{
}

void Obstacles::handleMove()
{
	y_val = 15;
	rect_.y += y_val;
	if (rect_.y > SCREEN_HEIGHT)
	{
		rect_.y = -HEIGHT_OBSTACLE;
		int rand_x = rand() % 410 + 10;
		rect_.x = rand_x;
	}
}
