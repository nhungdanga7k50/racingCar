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
	if (Init() == false)
	{
		return 0;
	}
	//Khởi tạo các biến điều chỉnh vòng lặp
	bool is_quit = false;
	bool is_collision = false;
	UINT32 startTime = 0;
	//Show ảnh nền
	int menu = commonFun::showMenu(g_screen, g_text);
	if (menu == 0)
	{
		return 0;
	}
	//Tạo vòng lặp do_while để điều chỉnh lựa chọn
	int chooseplay = 1;
	do
	{
		// Load ảnh đường đua của game
		g_bground1 = commonFun::LoadImage("image/race.png");
		g_bground2 = commonFun::LoadImage("image/menu.png");
		if (g_bground1 == NULL || g_bground2 == NULL)
		{
			return 0;
		}
		// Tạo, level, thời gian, điểm cho game
		Text level;
		level.SetColor(Text::RED_TEXT);
		Text time;
		time.SetColor(Text::RED_TEXT);
		Text score;
		score.SetColor(Text::RED_TEXT);
		// Load xe của người chơi
		MainObject myCar;
		myCar.SetRect(200, 400);
		bool is_load = myCar.LoadImg("image/mycar1.png");
		if (is_load == false)
		{
			return 0;
		}
		// Tạo các chướng ngại vật trên đường đi
		Obstacles *p_obstacles = new Obstacles[NUM_OBSTACLE];
		for (int i = 0; i< NUM_OBSTACLE; i++)
		{
			Obstacles *p_obstacle = (p_obstacles + i);
			if (p_obstacle != NULL)
			{
				bool is_load;
				int choice = rand() % 3;
				switch (choice)
				{
				case 0: is_load = p_obstacle->LoadImg("image/greencar.png");
					break;
				case 1: is_load = p_obstacle->LoadImg("image/redcar.png");
					break;
				case 2: is_load = p_obstacle->LoadImg("image/bluecar.png");
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
		// Tạo biến điều chỉnh level, điểm
		unsigned int addScore = 0;
		unsigned int iLevel = 0;
		// Bắt sự kiện bàn phím và xử lý
		int bk_y = 0;
		while (!is_quit)
		{
			if (is_quit == false)
			{
				Mix_PlayChannel(-1, g_sound, 0);
			}		
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
				is_collision = commonFun::checkCollision(p_obstacle->GetRect(), myCar.GetRect());
				if (is_collision == true)
				{
					commonFun::ApplySurface(gameOver, g_screen, 0, 0);
					is_quit = true;
					break;
				}
			}
			//Hiển thị level
			iLevel = 1 + addScore / 300;
			std::string strLevel("Level: ");
			std::string val_level = std::to_string(iLevel);
			strLevel += val_level;
			level.SetText(strLevel);
			level.RenderText(g_text, g_screen);
			//Hiển thị thời gian
			std::string strTime("Time: ");
			std::string val_time = std::to_string(SDL_GetTicks() / 1000 - startTime);
			strTime += val_time;
			time.SetText(strTime);
			time.SetRect(500, 200);
			time.RenderText(g_text, g_screen);
			// Hiển thị điểm
			addScore = (SDL_GetTicks() / 1000 - startTime) * 15;
			std::string val_score = std::to_string(addScore);
			std::string strScore("Score: ");
			strScore += val_score;
			score.SetText(strScore);
			score.SetRect(500, 320);
			score.RenderText(g_text, g_screen);
			SDL_Delay(60 / iLevel);
			if (SDL_Flip(g_screen) == -1)
			{
				return 0;
			}
		}
		delete[] p_obstacles;
		commonFun::cleanUp();
		//Đặt lại giá trị cho biến điều khiển vòng lặp
		is_quit = false;
		is_collision = false;
		//Show menu chương trình khi thua
		int is_choose = commonFun::choose(g_screen, g_text, addScore);
		SDL_Flip(g_screen);
		if (is_choose == 0)
		{
			chooseplay = 0;
			is_quit = true;
		}
		else
		{
			chooseplay = 1;
			startTime = SDL_GetTicks() / 1000;
		}
	} while (chooseplay != 0);
	TTF_Quit();
	SDL_Quit();
	return 1;
}
