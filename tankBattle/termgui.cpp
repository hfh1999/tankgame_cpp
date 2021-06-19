#include "termgui.h"

TermioApp::TermioApp():Terminal()
{
	termapp_in = GetStdHandle(STD_INPUT_HANDLE);
	event_loop = std::thread(&TermioApp::eventloop, this);
}

TermioApp::~TermioApp()
{
	loop_flag = false;//ֹͣevent loop flag
	event_loop.join();
	std::cout << "[TermioApp]event loop terminate";
}

void TermioApp::key_event(KeyEvent term_event)
{
	//do nothing
}

void TermioApp::renderDrawables()
{
	//print the renderDrawables.
//	std::cout << "renderDrawables... obj1,obj2,obj3\n";
	for (auto item : obj_list)
	{
		if (item->visualable)
		{
			auto len = (item->relative_pos).size();
			auto pos_array = item->relative_pos;
			auto char_array = item->content;
			auto origin_point_x = item->origin_point.X;
			auto origin_point_y = item->origin_point.Y;
			auto old_point_x = item->old_point.X;
			auto old_point_y = item->old_point.Y;
			auto direct = item->direct;
			auto direct_old = item->old_direct;

			for (int index = 0; index < len; index++)
			{

				auto coord_to_erase = __coord_trans(COORD{ old_point_x + pos_array[index].X,old_point_y + pos_array[index].Y },direct_old);
				erase(coord_to_erase.X,coord_to_erase.Y);
			}
			for (int index = 0; index < len; index++)
			{
				auto coord_to_draw = __coord_trans(COORD{ pos_array[index].X + origin_point_x, pos_array[index].Y + origin_point_y },direct );
				draw(coord_to_draw.X,coord_to_draw.Y,char_array[index]);
			}
		}
	}
}


bool TermioApp::addDrawable(shared_ptr<Drawable> in_obj, bool is_visuable)
{
	if (in_obj->is_managed)
		return false;  //已经加入过,加入失败
	else
	{
		obj_list.push_back(in_obj);
		in_obj->is_managed = true;
	}
}

bool TermioApp::removeDrawable(std::string id)
{
	return false;
}

bool TermioApp::setVisuable(std::string id, bool visuable_value)
{
	return false;
}


COORD TermioApp::__coord_trans(COORD in_coord, Drawable::DrawDirect direct)
{
	if (in_coord.X == 0 && in_coord.Y == 0)
		return COORD{ 0,0 };
	else
	{
		switch (direct)
		{
		case Drawable::DrawDirect::Up:
			return in_coord;
			break;
		case Drawable::DrawDirect::Down:
			return COORD{ in_coord.X,-in_coord.Y };
			break;
		case Drawable::DrawDirect::Left:
			return COORD{ -in_coord.Y,in_coord.X };
			break;
		case Drawable::DrawDirect::Right:
			return COORD{ in_coord.Y,in_coord.X };
			break;

		}
	}
}

void TermioApp::eventloop()
{
	INPUT_RECORD irInBuf[128];
	DWORD cNumRead;//读取了多少记录
	while(loop_flag)
	{
		/*	get some event */
		//get input and transmit it as io_event class
		//call input_event;
		ReadConsoleInput(termapp_in, irInBuf, 128, &cNumRead);
		for (DWORD counter = 0; counter < cNumRead; counter++)
		{
			switch (irInBuf[counter].EventType)
			{
			case FOCUS_EVENT:
				break;
			case KEY_EVENT:
				//std::cout << "[eventloop]key event\n";
				key_event(KeyEvent(&irInBuf[counter]));
				break;
			case MOUSE_EVENT:
				//std::cout << "[eventloop]mouse event\n";
				break;
			case WINDOW_BUFFER_SIZE_EVENT:
				//std::cout << "[eventloop]window buffer size event.\n";
				break;
			//case MENU_EVENT: //内部使用,此处忽略
			default:
				break;
			}
		}
		//std::cout << cNumRead << "events readed" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

KeyEvent::KeyEvent(INPUT_RECORD * input_record)
{
	key_code = input_record->Event.KeyEvent.wVirtualKeyCode;
	key_down = input_record->Event.KeyEvent.bKeyDown;
	repeat_count = input_record->Event.KeyEvent.wRepeatCount;
}

void KeyEvent::Debug()
{
	//std::cout << "[InputEvent Debug]\n";
}

