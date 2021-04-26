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
	//Các biến lấy tọa độ của object 1
	int left1 = object1.x + 5;
	int right1 = object1.x + object1.w - 5;
	int head1 = object1.y + object1.h - 5;
	int bottom1 = object1.y + 5;
	//Các biến lấy tọa độ của object 2
	int left2 = object2.x + 5;
	int right2 = object2.x + object2.w - 5;
	int head2 = object2.y + object2.h - 5;
	int bottom2 = object2.y + 5;

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

//Hàm show menu game
int commonFun::showMenu(SDL_Surface * des, TTF_Font * font)
{
	g_background = LoadImage("background.jpg");
	g_race = LoadImage("racing.png");
	if (g_background == NULL || g_race == NULL)
	{
		return 0;
	}
	//Set hai vị trí cho hai text
	SDL_Rect pos[2];
	pos[0].x = 140;
	pos[0].y = 460;
	pos[1].x = 420;
	pos[1].y = 460;
	//Tạo font chữ Play
	Text text_menu;
	text_menu.SetText("Play");
	text_menu.SetColor(Text::WHITE_TEXT);
	text_menu.SetRect(pos[0].x, pos[0].y);
	//Tạo font chữ Exit
	Text exit;
	exit.SetText("Exit");
	exit.SetColor(Text::WHITE_TEXT);
	exit.SetRect(pos[1].x, pos[1].y);

	SDL_Event e;
	int xm = 0;
	int ym = 0;
	while (true)
	{
		commonFun::ApplySurface(g_background, des, 0, 0);
		commonFun::ApplySurface(g_race, des, 210, 50);
		exit.RenderText(font, des);
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
				if (xm >= pos[0].x&&xm <= pos[0].x + 50 && ym >= pos[0].y&&ym <= pos[0].y + 20)
				{
					text_menu.SetColor(Text::RED_TEXT);
				}
				else
				{
					text_menu.SetColor(Text::WHITE_TEXT);
				}
				if (xm >= pos[1].x&&xm <= pos[1].x + 40 && ym >= pos[1].y&&ym <= pos[1].y + 20)
				{
					exit.SetColor(Text::RED_TEXT);
				}
				else
				{
					exit.SetColor(Text::WHITE_TEXT);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				xm = e.button.x;
				ym = e.button.y;
				if (xm >= pos[0].x&&xm <= pos[0].x + 50 && ym >= pos[0].y&&ym <= pos[0].y + 20)
				{
					return 1;
				}
				if (xm >= pos[1].x&&xm <= pos[1].x + 40 && ym >= pos[1].y&&ym <= pos[1].y + 20)
				{
					return 0;
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
//Hàm xử lý lựa chọn của người chơi
int commonFun::choose(SDL_Surface * des, TTF_Font * font, int addScore)
{
	gameOver = commonFun::LoadImage("gameOver.png");
	if (gameOver == NULL)
	{
		return 0;
	}
	//Set ba vị trí cho text
	SDL_Rect pos[3];
	pos[0].x = 250;
	pos[0].y = 420;
	pos[1].x = 160;
	pos[1].y = 480;
	pos[2].x = 380;
	pos[2].y = 480;
	//Tạo font score
	Text score;
	score.SetColor(Text::RED_TEXT);
	score.SetRect(pos[0].x, pos[0].y);
	std::string score_val = std::to_string(addScore);
	std::string strScore("Score: ");
	strScore += score_val;
	score.SetText(strScore);
	//Tạo font exit
	Text exit;
	exit.SetText("Exit");
	exit.SetColor(Text::WHITE_TEXT);
	exit.SetRect(pos[1].x, pos[1].y);
	//Tạo font playAgain
	Text playAgain;
	playAgain.SetText("Play Again");
	playAgain.SetColor(Text::WHITE_TEXT);
	playAgain.SetRect(pos[2].x, pos[2].y);

	SDL_Event e;
	int xm = 0, ym = 0;
	while (true)
	{
		commonFun::ApplySurface(gameOver, des, 0, 0);
		score.RenderText(font, des);
		exit.RenderText(font, des);
		playAgain.RenderText(font, des);
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				return 0;
			case SDL_MOUSEMOTION:
				xm = e.motion.x;
				ym = e.motion.y;
				if (xm >= pos[1].x&&xm <= pos[1].x + 50 && ym >= pos[1].y&&ym <= pos[1].y + 20)
				{
					exit.SetColor(Text::RED_TEXT);
				}
				else
				{
					exit.SetColor(Text::WHITE_TEXT);
				}
				if (xm >= pos[2].x&&xm <= pos[2].x + 140 && ym >= pos[2].y&&ym <= pos[2].y + 20)
				{
					playAgain.SetColor(Text::RED_TEXT);
				}
				else
				{
					playAgain.SetColor(Text::WHITE_TEXT);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				xm = e.button.x;
				ym = e.button.y;
				if (xm >= pos[1].x&&xm <= pos[1].x + 50 && ym >= pos[1].y&&ym <= pos[1].y + 20)
				{
					return 0;
				}
				if (xm >= pos[2].x&&xm <= pos[2].x + 140 && ym >= pos[2].y&&ym <= pos[2].y + 20)
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
