#ifndef BaseObject_H_
#define BaseObject_H_
#include"commonFunction.h"

//Tạo một lớp xử lý chung cho nhân vật
class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void show(SDL_Surface *des);
	bool LoadImg(const char *file_name);

	void SetRect(const int &x, const int &y) { rect_.x = x, rect_.y = y; }
	SDL_Rect GetRect() const { return rect_; }
	SDL_Surface *GetObject() { return p_object; }
protected:
	SDL_Rect rect_;
	SDL_Surface *p_object;
};

#endif