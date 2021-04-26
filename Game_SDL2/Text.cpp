#include "Text.h"

//khởi tạo giá trị ban đầu cho lớp text
Text::Text()
{
	rect_.x = 500;
	rect_.y = 80;
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
}

Text::~Text()
{
}

//Hàm đặt màu cho font chữ
void Text::SetColor(const int & type)
{
	if (type == RED_TEXT)
	{
		text_color = { 255, 0, 0 };
	}
	else if(type == WHITE_TEXT)
	{
		text_color = { 255, 255, 255 };
	}
	else
	{
		text_color = { 0, 0, 0 };
	}
}

//Hàm viết chữ lên màn hình
void Text::RenderText(TTF_Font * font, SDL_Surface * des)
{
	p_object = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
	show(des);
}
