#include <iostream>
#include <string>
#include <Windows.h>
const LPCWSTR Cursor_Up = L"\x1b[A";//�������
const LPCWSTR Cursor_Down = L"\x1b[B";
const LPCWSTR Cursor_Left = L"\x1b[D";//�������
const LPCWSTR Cursor_Right = L"\x1b[C";
const LPCWSTR Set_Terminal_Width132 = L"\x1b[?3h";//�趨�ն˿��Ϊ132
const LPCWSTR Cursor_To_RightButtom = L"\x1b[999;999H";//��굽�ﴰ�������½ǵ�λ��
void aquire_terminal_size(HANDLE & handle);
struct TermChar {//��ʾһ�����Ի���terminal����һ������λ�õķ���.
	static const LPCWSTR Default;
	static const LPCWSTR Foreground_Bold;//����
	static const LPCWSTR Foreground_No_Bold;//ȡ������
	static const LPCWSTR Underline;//�»���
	static const LPCWSTR No_Underline;//ȡ���»���
	static const LPCWSTR Negative;//����ǰ����ɫ
	static const LPCWSTR Positive;//ȡ������
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

/*�ṩ���������ͼ����*/
class Terminal {//�����Terminal��Ӧ����ʼ��ֻ����һ��
private:
	HANDLE terminal_out;
	COORD cursor_pos;//����λ��

protected:
	SMALL_RECT display_size;//�ն˵���ʾ��С
public:
	static enum Direct{Up,Down,Left,Right};

	Terminal();//����һ��terminal��
	virtual ~Terminal();
	void draw(SHORT x,SHORT y,TermChar ch);//дһ������
	void drawBlank(SHORT x, SHORT y,LPCWSTR color);
	void erase(SHORT x, SHORT y);//����һ������
	void DrawLine(COORD start_point, Direct direct, SHORT lenth,TermChar ch);//��һ����ֱ��
	void DrawLineBlank(COORD start_point, Direct direct, SHORT lenth,LPCWSTR color);
	void DrawRect(COORD start_point, SHORT cols, SHORT rows, TermChar ch);//��һ���վ���
	void DrawRectBlank(COORD start_point, SHORT cols, SHORT rows, LPCWSTR color);
	void CopyRect();//����һ��Rect��ָ��λ��
	void CutRect();//����һ��Rect��ָ��λ��
	void cls();//�����Ļ
};
