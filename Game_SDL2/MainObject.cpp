#include"MainObject.h"

MainObject::MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.h = HEIGHT_MAIN_OBJECT;
	rect_.w = WIDTH_MAIN_OBJECT;
	x_val = 0;
	y_val = 0;
}

MainObject::~MainObject()
{

}
 
// Bắt sự kiện bàn phím
void MainObject::handleInputAction(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			x_val += WIDTH_MAIN_OBJECT / 3;
			break;
		case SDLK_LEFT:
			x_val -= WIDTH_MAIN_OBJECT / 3;
			break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			x_val -= WIDTH_MAIN_OBJECT / 3;
			break;
		case SDLK_LEFT:
			x_val += WIDTH_MAIN_OBJECT / 3;
			break;
		}
	}
}

 // Xử lý sự kiện bàn phím
void MainObject::Move()
{
	int edge = 10;
	rect_.x += x_val;
	if (rect_.x < 0)
	{
		rect_.x = edge;
	}
	else if (rect_.x + WIDTH_MAIN_OBJECT > WIDTH_RACE - edge)
	{
		rect_.x = WIDTH_RACE - WIDTH_MAIN_OBJECT - edge;
	}
}
