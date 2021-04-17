#ifndef MainObject_H_
#define MainObject_H_
#include"commonFunction.h"
#include"BaseObject.h"

#define WIDTH_MAIN_OBJECT 60
#define HEIGHT_MAIN_OBJECT 100

//Tạo một lớp xử lý nhân vật chính
class MainObject :public BaseObject
{
public:
	MainObject();
	~MainObject();
	void handleInputAction(SDL_Event event);
	void Move();
private:
	int x_val;
	int y_val;
};
#endif