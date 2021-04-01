#ifndef Obstacles_H_
#define Obstacles_H_
#include"commonFunction.h"
#include"BaseObject.h"

#define WIDTH_OBSTACLE 60
#define HEIGHT_OBSTACLE 100

class Obstacles :public BaseObject
{
public:
	Obstacles();
	~Obstacles();
	void handleMove();
	void set_x_val(const int &val) { x_val = val; }
	void set_y_val(const int &val) { y_val = val; }
	int get_x_val() const { return x_val; }
	int get_y_val() const { return y_val; }

private:
	int x_val;
	int y_val;
};

#endif
