#pragma once
#include "drawable.h"
class DrawableObj
{
public:
	DrawableObj() = delete;
	DrawableObj(std::shared_ptr<Drawable> inDrawable):ptr_to_Drawable(inDrawable){}

	/*将Drawabe的接口暴露出来*/
	void move_left(SHORT step);
	void move_right(SHORT step);
	void move_up(SHORT step);
	void move_down(SHORT step);
	void turn_left();
	void turn_right();
	void turn_up();
	void turn_down();
	void set_visualable();
	void set_unvisualable();
	void set_static(bool flag);
	COORD ret_coord() { return ptr_to_Drawable->ret_coord(); }
private:
	std::shared_ptr<Drawable> ptr_to_Drawable;
};

