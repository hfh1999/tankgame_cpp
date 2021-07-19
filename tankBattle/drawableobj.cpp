#include "drawableobj.h"

/*将Drawabe的接口暴露出来*/

void DrawableObj::move_left(SHORT step) {
	ptr_to_Drawable->move_left(step);
}

void DrawableObj::move_right(SHORT step)
{
	ptr_to_Drawable->move_right(step);
}

void DrawableObj::move_up(SHORT step)
{
	ptr_to_Drawable->move_up(step);
}

void DrawableObj::move_down(SHORT step)
{
	ptr_to_Drawable->move_down(step);
}

void DrawableObj::move(COORD in_coord)
{
	ptr_to_Drawable->move(in_coord);
}

void DrawableObj::turn_left()
{
	ptr_to_Drawable->turn_left();
}

void DrawableObj::turn_right()
{
	ptr_to_Drawable->turn_right();
}

void DrawableObj::turn_up()
{
	ptr_to_Drawable->turn_up();
}

void DrawableObj::turn_down()
{
	ptr_to_Drawable->turn_down();
}

void DrawableObj::set_visualable()
{
	ptr_to_Drawable->set_visualable();
}

void DrawableObj::set_unvisualable()
{
	ptr_to_Drawable->set_unvisualable();
}

void DrawableObj::set_static(bool flag)
{
	ptr_to_Drawable->set_static(flag);
}

