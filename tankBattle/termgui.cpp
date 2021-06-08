#include "termgui.h"

TermioApp::TermioApp()
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

void TermioApp::input_event(InputEvent term_event)
{
	//do nothing
}

void TermioApp::renderDrawables()
{
	//print the renderDrawables.
	std::cout << "renderDrawables... obj1,obj2,obj3\n";
}


bool TermioApp::addDrawable(shared_ptr<DrawableObj> in_obj, bool is_visuable)
{
	return false;
}

bool TermioApp::removeDrawable(std::string id)
{
	return false;
}

bool TermioApp::setVisuable(std::string id, bool visuable_value)
{
	return false;
}

WrapDrawablObj TermioApp::getDrawable(std::string id)
{
	return WrapDrawablObj();
}

bool TermioApp::moveLeft(std::string id, SHORT steps)
{
	return false;
}

bool TermioApp::moveRight(std::string id, SHORT steps)
{
	return false;
}

bool TermioApp::moveUp(std::string id, SHORT steps)
{
	return false;
}

bool TermioApp::moveDown(std::string id, SHORT steps)
{
	return false;
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
				input_event(InputEvent(&irInBuf[counter]));
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
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
}

InputEvent::InputEvent(INPUT_RECORD * input_record)
{
	key_code = input_record->Event.KeyEvent.wVirtualKeyCode;
	key_down = input_record->Event.KeyEvent.bKeyDown;
	repeat_count = input_record->Event.KeyEvent.wRepeatCount;
}

void InputEvent::Debug()
{
	//std::cout << "[InputEvent Debug]\n";
}


DrawableObj::DrawableObj(std::string in_str)
{
	if (in_str == "look")//当指定生成look图形时才执行
	{
		id = std::string("look");
		TermChar ch(' ', TermChar::Foreground_Default, TermChar::Background_Yellow);//黄色空格
		for (SHORT i = 1; i <= 6; i++)//画出四个竖杠
		{
			for (SHORT j = 0; j < 4; j++)
			{
				relative_pos.push_back(COORD{ 1 + 4 * j,i });
				content.push_back(ch);
			}
		}
	}
	else {
		//以x0,y0;x1,y1;x2,y2;格式绘图.
	}
}

const std::vector<COORD>& DrawableObj::ReturnPos()
{
	return relative_pos;
}

const std::vector<TermChar>& DrawableObj::Returncontent()
{
	return content;
}


