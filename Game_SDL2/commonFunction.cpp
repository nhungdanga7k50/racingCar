#include"commonFunction.h"
#include"Text.h"

// Hàm load ảnh từ đường dẫn cho trước
SDL_Surface *commonFun::LoadImage(std::string file_path)
{
	SDL_Surface *load_image = NULL;
	SDL_Surface *optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str());
	if (load_image != NULL)
	{
		optimize_image = SDL_DisplayFormat(load_image);
		if (optimize_image != NULL)
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 0xff, 0xff, 0xff);
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
		SDL_FreeSurface(load_image);
	}
	return optimize_image;
}

// Hàm ghép ảnh
void commonFun::ApplySurface(SDL_Surface *screen, SDL_Surface *des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(screen, NULL, des, &offset);
}

// Hàm xử lý khi va chạm xảy ra
bool commonFun::checkCollision(const SDL_Rect & object1, const SDL_Rect & object2)
{
	int left1 = object1.x + 10;
	int right1 = object1.x + object1.w - 10;
	int head1 = object1.y + object1.h - 5;
	int bottom1 = object1.y;

	int left2 = object2.x + 10;
	int right2 = object2.x + object2.w - 10;
	int head2 = object2.y + object2.h - 5;
	int bottom2 = object2.y;

	if (left1 >= left2 && left1 <= right2 )
	{
		if (head1 >= bottom2 && head1 <= head2)
			return true;
		if (bottom1 >= bottom2 && bottom1 <= head2)
			return true;
	}
	if (right1 >= left2 && right1 <= right2)
	{
		if (head1 >= bottom2 && head1 <= head2)
			return true;
		if (bottom1 >= bottom2 && bottom1 <= head2)
			return true;
	}
	return false;	
}

int commonFun::showMenu(SDL_Surface * des, TTF_Font * font)
{
	g_background = LoadImage("background.jpg");
	g_race = LoadImage("racing.png");
	if (g_background == NULL && g_race == NULL)
	{
		return 0;
	}
	SDL_Rect pos_play;
	pos_play.x = 300;
	pos_play.y = 450;

	Text text_menu;
	text_menu.SetText("Play");
	text_menu.SetColor(Text::WHITE_TEXT);
	text_menu.SetRect(pos_play.x, pos_play.y);

	SDL_Event e;
	int xm = 0;
	int ym = 0;
	while (true)
	{
		commonFun::ApplySurface(g_background, des, 0, 0);
		commonFun::ApplySurface(g_race, des, 210, 50);
		text_menu.RenderText(font, des);
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				return 0;
			case SDL_MOUSEMOTION:
				xm = e.motion.x;
				ym = e.motion.y;
				if (xm >= pos_play.x&&xm <= pos_play.x + 40
					&& ym >= pos_play.y&&ym <= pos_play.y + 20)
				{
					text_menu.SetColor(Text::RED_TEXT);
				}
				else
				{
					text_menu.SetColor(Text::WHITE_TEXT);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				xm = e.button.x;
				ym = e.button.y;
				if (xm >= pos_play.x&&xm <= pos_play.x + 40
					&& ym >= pos_play.y&&ym <= pos_play.y + 20)
				{
					return 1;
				}
				break;
			default:
				break;
			}
		}
		SDL_Flip(des);
	}
	return 0;
}

// Hàm giải phóng các phần tử
void commonFun::cleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bground1);
	SDL_FreeSurface(g_bground2);
}