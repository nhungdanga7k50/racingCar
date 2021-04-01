#include<iostream>
#include"commonFunction.h"
#include"MainObject.h"
#include"Obstacles.h"
#include"Text.h"
#undef main
using namespace std;

TTF_Font* g_text = NULL;
// Khởi tạo các hàm có sẵn trong thư viện SDL
bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BPP, SDL_SWSURFACE);
	if (g_screen == NULL)
	{
		return false;
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}
	g_sound = Mix_LoadWAV("road.wav");
	if (g_sound == NULL)
	{
		return false;
	}
	if (TTF_Init() == -1)
	{
		return false;
	}
	g_text = TTF_OpenFont("ANTSYPAN.ttf", 20);
	if (g_text == NULL)
	{
		return false;
	}
	return true;
}
	// Chương trình chính
int main(int argc, char *argv[])
{
	bool is_quit = false;
	if (Init() == false)
	{
		return 0;
	}
	// Load ảnh đường đua của game
	g_bground1 = commonFun::LoadImage("race.png");
	g_bground2 = commonFun::LoadImage("Menu.jpg");
	gameOver = commonFun::LoadImage("gameOver.png");
	if (g_bground1 == NULL || g_bground2 == NULL|| gameOver == NULL)
	{
		return 0;
	}
	// Tạo, level, thời gian, quãng đường cho game
	Text level;
	level.SetColor(Text::RED_TEXT);
	Text time;
	time.SetColor(Text::RED_TEXT);
	Text meter;
	meter.SetColor(Text::RED_TEXT);
	// Load xe của người chơi
	MainObject myCar;
	myCar.SetRect(200, 400);
	if (myCar.LoadImg("mycar1.png") == 0)
	{
		return 0;
	}
	// Tạo các chướng ngại vật trên đường đi
	Obstacles *p_obstacles = new Obstacles[NUM_OBSTACLE];
	for(int i=0; i< NUM_OBSTACLE; i++)
	{
		Obstacles *p_obstacle = (p_obstacles+i);
		if (p_obstacle != NULL)
		{
			bool is_load;
			int choice = rand() % 3;
			switch (choice)
			{
			case 0: is_load = p_obstacle->LoadImg("greencar.png");
				break;
			case 1: is_load = p_obstacle->LoadImg("redcar.png");
				break;
			case 2: is_load = p_obstacle->LoadImg("bluecar.png");
				break;
			}
			if (is_load == false)
			{
				return 0;
			}
			int rand_x = rand() % 410;
			p_obstacle->SetRect(rand_x, -i * 160);
		}
	}
	// Tạo biến điều chỉnh level, quãng đường
	unsigned int addMeter = 0;
	unsigned int iLevel = 0;
	//Show menu chương trình
	int menu = commonFun::showMenu(g_screen, g_text);
	if (menu == 0)
	{
		is_quit = true;
	}
	// Bắt sự kiện bàn phím và xử lý
	int bk_y = 0;
	while (!is_quit)
	{
		Mix_PlayChannel(-1, g_sound, 0);
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			myCar.handleInputAction(g_event);
		}
		myCar.Move();
		// Show ảnh nền và xe
		commonFun::ApplySurface(g_bground2, g_screen, 480, 0);
		bk_y += 20;
		commonFun::ApplySurface(g_bground1, g_screen, 0, bk_y);
		commonFun::ApplySurface(g_bground1, g_screen, 0, bk_y - SCREEN_HEIGHT);
		if (bk_y > SCREEN_HEIGHT)
		{
			bk_y = 0;
		}
		myCar.show(g_screen);
		// Xử lý khi xảy ra va chạm
		for (int i = 0; i < NUM_OBSTACLE; i++)
		{
			Obstacles * p_obstacle = (p_obstacles + i);
			if (p_obstacle != NULL)
			{
				p_obstacle->handleMove();
				p_obstacle->show(g_screen);
			}
			bool is_collision = commonFun::checkCollision(p_obstacle->GetRect(), myCar.GetRect());
			if (is_collision == true)
			{
				commonFun::ApplySurface(gameOver, g_screen, 0, 0);
				is_quit = true;
				break;
			}
		}
		//Hiển thị level
		iLevel = 1 + addMeter / 300;
		std::string strLevel("Level: ");
		std::string val_level = std::to_string(iLevel);
		strLevel += val_level;
		level.SetText(strLevel);
		level.RenderText(g_text, g_screen);
		//Hiển thị thời gian
		std::string strTime("Time: ");
		UINT32 time_val = SDL_GetTicks() / 1000;
		std::string val_time = std::to_string(time_val);
		strTime += val_time;
		time.SetText(strTime);
		time.SetRect(500, 200);
		time.RenderText(g_text, g_screen);
		// Hiển thị quãng đường 
		addMeter = time_val * 15;
		std::string val_meter = std::to_string(addMeter);
		std::string strMeter("Meter: ");
		strMeter += val_meter;
		meter.SetText(strMeter);
		meter.SetRect(500, 320);
		meter.RenderText(g_text, g_screen);
		SDL_Delay(50 / iLevel);
		if (SDL_Flip(g_screen) == -1)
		{
			return 0;
		}
	}
	delete [] p_obstacles;
	commonFun::cleanUp();
	SDL_Quit();
	return 1;
}