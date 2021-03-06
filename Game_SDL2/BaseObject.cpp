#include"BaseObject.h"
//Khởi tạo giá trị ban đầu cho nhân vật
BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object = NULL;
}

BaseObject::~BaseObject()
{
	if (p_object != NULL)
	{
		SDL_FreeSurface(p_object);
		p_object = NULL;
	}
}
 
//Hàm load ảnh cho nhân vật
bool BaseObject::LoadImg(const char * file_name)
{
	p_object = commonFun::LoadImage(file_name);
	if (p_object == NULL)
		return false;
	return true;
}

//Hàm chiếu ảnh lên màn hình
void BaseObject::show(SDL_Surface * des)
{
	if (p_object != NULL)
	{
		 commonFun::ApplySurface(p_object, des, rect_.x, rect_.y);
	}
}


