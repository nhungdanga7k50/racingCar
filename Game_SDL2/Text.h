#ifndef Text_H_
#define Text_H_
#include"BaseObject.h"
#include<string>
#include<SDL_ttf.h>

//Tạo một lớp text để viết chữ
class Text : public BaseObject
{
public:
	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
	};
	Text();
	~Text();

	void SetText(const std::string& text) { str_val = text;}
	void SetColor(const int &type);
	void RenderText(TTF_Font* font, SDL_Surface* des);

private:
	std :: string str_val;
	SDL_Color text_color;
};
#endif

