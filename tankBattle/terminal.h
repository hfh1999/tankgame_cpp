#include <iostream>
#include <string>
#include <Windows.h>
const LPCWSTR Cursor_Up = L"\x1b[A";//光标向上
const LPCWSTR Cursor_Down = L"\x1b[B";
const LPCWSTR Cursor_Left = L"\x1b[D";//光标向左
const LPCWSTR Cursor_Right = L"\x1b[C";
const LPCWSTR Set_Terminal_Width132 = L"\x1b[?3h";//设定终端宽度为132
const LPCWSTR Cursor_To_RightButtom = L"\x1b[999;999H";//光标到达窗口最右下角的位置
void aquire_terminal_size(HANDLE & handle);
struct TermChar {//表示一个可以画在terminal任意一个几何位置的符号.
	static const LPCWSTR Default;
	static const LPCWSTR Foreground_Bold;//高亮
	static const LPCWSTR Foreground_No_Bold;//取消高亮
	static const LPCWSTR Underline;//下划线
	static const LPCWSTR No_Underline;//取消下划线
	static const LPCWSTR Negative;//交换前后景颜色
	static const LPCWSTR Positive;//取消交换
	static const LPCWSTR Foreground_Black;
	static const LPCWSTR Foreground_Red;
	static const LPCWSTR Foreground_Green;
	static const LPCWSTR Foreground_Yellow;
	static const LPCWSTR Foreground_Blue;
	static const LPCWSTR Foreground_Magenta;
	static const LPCWSTR Foreground_Cyan;
	static const LPCWSTR Foreground_White;
	static const LPCWSTR Foreground_Default;
	static const LPCWSTR Background_Black;
	static const LPCWSTR Background_Red;
	static const LPCWSTR Background_Green;
	static const LPCWSTR Background_Yellow;
	static const LPCWSTR Background_Blue;
	static const LPCWSTR Background_Magenta;
	static const LPCWSTR Background_Cyan;
	static const LPCWSTR Background_White;
	static const LPCWSTR Background_Default;
	static const LPCWSTR Bright_Foreground_Black;
	static const LPCWSTR Bright_Foreground_Red;
	static const LPCWSTR Bright_Foreground_Green;
	static const LPCWSTR Bright_Foreground_Yellow;
	static const LPCWSTR Bright_Foreground_Blue;
	static const LPCWSTR Bright_Foreground_Magenta;
	static const LPCWSTR Bright_Foreground_Cyan;
	static const LPCWSTR Bright_Foreground_White;
	static const LPCWSTR Bright_Foreground_Default;
	static const LPCWSTR Bright_Background_Black;
	static const LPCWSTR Bright_Background_Red;
	static const LPCWSTR Bright_Background_Green;
	static const LPCWSTR Bright_Background_Yellow;
	static const LPCWSTR Bright_Background_Blue;
	static const LPCWSTR Bright_Background_Magenta;
	static const LPCWSTR Bright_Background_Cyan;
	static const LPCWSTR Bright_Background_White;
	static const LPCWSTR Bright_Background_Default;

	TermChar(char in_content, LPCWSTR foregroud_attr_in, LPCWSTR backgroud_attr_in);
	LPCWSTR GetForegroudAttr();
	LPCWSTR GetBackgroudAttr();
	char GetContent();
private:
	char content;
	LPCWSTR foregroud_attribute;
	LPCWSTR backgroud_attribute;

};

/*提供最基本的作图功能*/
class Terminal {//这里的Terminal类应当是始终只创建一个
private:
	HANDLE terminal_out;
	COORD cursor_pos;//光标的位置

protected:
	SMALL_RECT display_size;//终端的显示大小
public:
	static enum Direct{Up,Down,Left,Right};

	Terminal();//创建一个terminal类
	virtual ~Terminal();
	void draw(SHORT x,SHORT y,TermChar ch);//写一个符号
	void drawBlank(SHORT x, SHORT y,LPCWSTR color);
	void erase(SHORT x, SHORT y);//擦除一个符号
	void DrawLine(COORD start_point, Direct direct, SHORT lenth,TermChar ch);//画一条正直线
	void DrawLineBlank(COORD start_point, Direct direct, SHORT lenth,LPCWSTR color);
	void DrawRect(COORD start_point, SHORT cols, SHORT rows, TermChar ch);//画一个空矩形
	void DrawRectBlank(COORD start_point, SHORT cols, SHORT rows, LPCWSTR color);
	void CopyRect();//复制一个Rect到指定位置
	void CutRect();//剪切一个Rect到指定位置
	void cls();//清除屏幕
};
