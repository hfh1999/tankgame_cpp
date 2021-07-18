#include "terminal.h"
void aquire_terminal_size(HANDLE & handle)
{
	using std::wcout;
	using std::cout;
	using std::wcin;
	using std::string;
	wcout << Set_Terminal_Width132;
	//	wcout << Cursor_To_RightButtom;
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	auto size = info.srWindow;
	cout << "display width:" << size.Right - size.Left << " display height:" << size.Bottom - size.Top;
	cout << "left = " << size.Left;
	cout << "top = " << size.Top;
}

const LPCWSTR TermChar::Default = L"\x1b[0m";
const LPCWSTR TermChar::Foreground_Bold = L"\x1b[1m";
const LPCWSTR TermChar::Foreground_No_Bold = L"\x1b[22m";
const LPCWSTR TermChar::Underline = L"\x1b[4m";
const LPCWSTR TermChar::No_Underline = L"\x1b[24m";
const LPCWSTR TermChar::Negative = L"\x1b[7m";
const LPCWSTR TermChar::Positive = L"\x1b[27m";
const LPCWSTR TermChar::Foreground_Black = L"\x1b[30m";
const LPCWSTR TermChar::Foreground_Red = L"\x1b[31m";
const LPCWSTR TermChar::Foreground_Green = L"\x1b[32m";
const LPCWSTR TermChar::Foreground_Yellow = L"\x1b[33m";
const LPCWSTR TermChar::Foreground_Blue = L"\x1b[34m";
const LPCWSTR TermChar::Foreground_Magenta = L"\x1b[35m";
const LPCWSTR TermChar::Foreground_Cyan = L"\x1b[36m";
const LPCWSTR TermChar::Foreground_White = L"\x1b[37m";
const LPCWSTR TermChar::Foreground_Default = L"\x1b[39m";
const LPCWSTR TermChar::Background_Black = L"\x1b[40m";
const LPCWSTR TermChar::Background_Red = L"\x1b[41m";
const LPCWSTR TermChar::Background_Green = L"\x1b[42m";
const LPCWSTR TermChar::Background_Yellow = L"\x1b[43m";
const LPCWSTR TermChar::Background_Blue = L"\x1b[44m";
const LPCWSTR TermChar::Background_Magenta = L"\x1b[45m";
const LPCWSTR TermChar::Background_Cyan = L"\x1b[46m";
const LPCWSTR TermChar::Background_White = L"\x1b[47m";
const LPCWSTR TermChar::Background_Default = L"\x1b[49m";
const LPCWSTR TermChar::Bright_Foreground_Black = L"\x1b[90m";
const LPCWSTR TermChar::Bright_Foreground_Red = L"\x1b[91m";
const LPCWSTR TermChar::Bright_Foreground_Green = L"\x1b[92m";
const LPCWSTR TermChar::Bright_Foreground_Yellow = L"\x1b[93m";
const LPCWSTR TermChar::Bright_Foreground_Blue = L"\x1b[94m";
const LPCWSTR TermChar::Bright_Foreground_Magenta = L"\x1b[95m";
const LPCWSTR TermChar::Bright_Foreground_Cyan = L"\x1b[96m";
const LPCWSTR TermChar::Bright_Foreground_White = L"\x1b[97m";
const LPCWSTR TermChar::Bright_Background_Black = L"\x1b[100m";
const LPCWSTR TermChar::Bright_Background_Red = L"\x1b[101m";
const LPCWSTR TermChar::Bright_Background_Green = L"\x1b[102m";
const LPCWSTR TermChar::Bright_Background_Yellow = L"\x1b[103m";
const LPCWSTR TermChar::Bright_Background_Blue = L"\x1b[104m";
const LPCWSTR TermChar::Bright_Background_Magenta = L"\x1b[105m";
const LPCWSTR TermChar::Bright_Background_Cyan = L"\x1b[106m";
const LPCWSTR TermChar::Bright_Background_White = L"\x1b[107m";
Terminal::Terminal()
{
	/*需要异常处理*/
	terminal_out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(terminal_out, &info);
	display_size.Left = info.srWindow.Left + 1;
	display_size.Right = info.srWindow.Right + 1;
	display_size.Top = info.srWindow.Top;
	display_size.Bottom = info.srWindow.Bottom;

	cursor_pos.X = 0;//左边是0;
	cursor_pos.Y = 0;//上边是0;
	DWORD oldmode;
	GetConsoleMode(terminal_out, &oldmode);
	oldmode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;//使得terminal sequence有效
	SetConsoleMode(terminal_out, oldmode);
	std::wcout << L"\x1b[?1049h";//启用备用缓冲区
	std::wcout << L"\x1b[?25l";//隐藏光标

	//test change font.
	//CONSOLE_FONT_INFOEX font_info;
	//font_info.cbSize = sizeof(font_info);
	//auto flag = GetCurrentConsoleFontEx(terminal_out, false, &font_info);
	//if (flag)
	//{ }
	//else
	//{
	//	std::cout << "failed"<<std::endl;
	//}
	//std::cout << "font size >  X = " << font_info.dwFontSize.X;
	//std::cout << "  Y = " << font_info.dwFontSize.Y<<std::endl;
	////std::cout << "font index" << font_info.nFont << std::endl;
	//auto name = std::wstring(font_info.FaceName);
	//std::cout << name.size();
	//std::wcout << name;
	//SetCurrentConsoleFontEx(terminal_out, false, &font_info);

	// 设置字体
	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	fontInfo.dwFontSize.X = 8;
	fontInfo.dwFontSize.Y = 8;
	fontInfo.FontFamily = TMPF_TRUETYPE;
	wcscpy_s(fontInfo.FaceName, L"Terminal");
	if (!SetCurrentConsoleFontEx(terminal_out, FALSE, &fontInfo)) {
		std::cout << "Failed to change the font: " << GetLastError();
	}

}

Terminal::~Terminal()
{
	std::wcout << L"\x1b[?1049l";//转回主缓冲区
}

void Terminal::draw(SHORT x, SHORT y, TermChar ch)
{
	//边界判定
	if (x < display_size.Left || y < display_size.Top || x > display_size.Right || y > display_size.Bottom)
		return;
	//移动到位置x,y
	std::wcout << "\x1b[" << y << ";" << x << "H";
	//更新cursor位置
	cursor_pos.X = x;
	cursor_pos.Y = y;
	//转换attribute
	std::wcout << ch.GetForegroudAttr();
	std::wcout << ch.GetBackgroudAttr();
	//写入字符
	std::wcout << ch.GetContent();
	//回到原来的attribute
	std::wcout << TermChar::Default;
}

void Terminal::drawBlank(SHORT x, SHORT y, LPCWSTR color)
{
	TermChar ch(' ', TermChar::Foreground_Default,color);
	draw(x, y, ch);
}

void Terminal::erase(SHORT x, SHORT y)
{
	draw(x, y, TermChar(' ', TermChar::Foreground_Default, TermChar::Background_Default));
}

void Terminal::DrawLine(COORD start_point, Direct direct, SHORT lenth, TermChar ch)
{
	SHORT count = 0;
	switch (direct)
	{
	case Direct::Down:
	case Direct::Up:
		SHORT y_step;
		if (direct == Down)
			y_step = 1;
		else
			y_step = -1;
		count = 0;
		while (count < lenth)
		{
			draw(start_point.X, start_point.Y + count * y_step, ch);
			count++;
		}
		break;
	case Direct::Left:
	case Direct::Right:
		SHORT x_step;
		if (direct == Left)
			x_step = -1;
		else
			x_step = 1;
		 count = 0;
		while (count < lenth)
		{
			draw(start_point.X + count * x_step, start_point.Y, ch);
			count++;
		}
	}
}

void Terminal::DrawLineBlank(COORD start_point, Direct direct, SHORT lenth, LPCWSTR color)
{
	TermChar ch(' ', TermChar::Foreground_Default,color);
	DrawLine(start_point, direct, lenth, ch);
}

void Terminal::DrawRect(COORD start_point, SHORT cols, SHORT rows, TermChar ch)
{
	//用直线来构成矩形
	COORD start = start_point;
	DrawLine(start, Direct::Right, cols, ch);
	start.X = start.X + cols - 1;
	DrawLine(start, Direct::Down, rows, ch);
	start.Y = start.Y + rows - 1;
	DrawLine(start, Direct::Left, cols, ch);
	start.X = start.X - cols + 1;
	DrawLine(start, Direct::Up, rows, ch);
}

void Terminal::DrawRectBlank(COORD start_point, SHORT cols, SHORT rows, LPCWSTR color)
{
	TermChar ch(' ', TermChar::Foreground_Default,color);
	DrawRect(start_point, cols, rows, ch);
}

void Terminal::CopyRect()
{
}

void Terminal::CutRect()
{
}

void Terminal::cls()
{
	std::wcout << L"\x1b[2J";
}

TermChar::TermChar(char in_content, LPCWSTR foregroud_attr_in, LPCWSTR backgroud_attr_in) :
	content(in_content), foregroud_attribute(foregroud_attr_in), backgroud_attribute(backgroud_attr_in)
{
}

LPCWSTR TermChar::GetForegroudAttr()
{
	return foregroud_attribute;
}

LPCWSTR TermChar::GetBackgroudAttr()
{
	return backgroud_attribute;
}

char TermChar::GetContent()
{
	return content;
}
