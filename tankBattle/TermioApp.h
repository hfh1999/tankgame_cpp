/*��teminal������input������*/
//��Ҫһ���¼�ѭ������event loop��������event
#include "terminal.h"
#include <thread>
#include <vector>
#include <memory>
using std::shared_ptr;
class DrawableObj {//ͼ�εĻ���
private:
	std::string id;//ͼ�εĶ��ص�id��
	std::vector<COORD> relative_pos;//�����ͼ�ε������Ͻ�Ϊԭ��
	std::vector<TermChar> content;//��Ӧλ�õķ���
public:
	DrawableObj(std::string in_str = "");//Ĭ�ϴ���һ���յ�,Ҳ������һ��look��ʶ(��Ҫָ��)
	//DrawableObj();//����ͼ�������ļ�����һ��
	//void ReturnData();//һ��ͨ�õĽӿ�,�����ڲ������Ի�ͼ
	const std::vector<COORD>& ReturnPos();
	const std::vector<TermChar>& Returncontent();
};
class WrapDrawablObj {//��װ���ͼ�ζ��������
public:
	bool moveLeft() {}//���ƶ���
	bool moveRight() {}//���ƶ���
	bool moveUp() {}//���ƶ���
	bool moveDown() {}//���ƶ���

};
class InputEvent {
private:
	WORD key_code;
	BOOL key_down;//status:up/down
	WORD repeat_count;//key is being held down.
public:
	InputEvent(INPUT_RECORD * input_record);
	void Debug();
};
class TermioApp :
	public Terminal
{
public:
	TermioApp();
	~TermioApp();

	virtual void input_event(InputEvent term_event);
	void renderDrawables();//��������drawable object��Ⱦ����

	bool addDrawable(shared_ptr<DrawableObj> in_obj, bool is_visuable = true);//����Drawable object
	bool removeDrawable(std::string id);//���涨id�Ķ�����б����Ƴ�
	bool setVisuable(std::string id, bool visuable_value = true);//���ö���Ŀɼ���
	/*���µĽӿ�Ӧ����drawobj�Ľӿ�ʵ��*/

	WrapDrawablObj getDrawable(std::string id);//��ȡ��ͼ�ζ���Ŀ���Ȩ
	bool moveLeft(std::string id, SHORT steps = 1);//���ƶ���
	bool moveRight(std::string id, SHORT steps = 1);//���ƶ���
	bool moveUp(std::string id, SHORT steps = 1);//���ƶ���
	bool moveDown(std::string id, SHORT steps = 1);//���ƶ���
private:
	HANDLE termapp_in;//�����ʶ��
	std::thread event_loop;
	bool loop_flag = true;//�Ƿ�ֹͣ�¼�ѭ��
	std::vector<shared_ptr<DrawableObj>> obj_list;//app�Ѿ�������Drawable object���б�

	void eventloop();//����¼�����ѭ��:��������(�¼�)

	//need event_call_back pointer here.

};
/*event loop*/
/*
	create global Event bind table:[events];
	loop{
	
	get a input data from console with "ReadConsoleInput()";
	look up the [events] to see if a events is happend;
	if happend{
		jump to the corresponding function;
	}else{
		continue;	
	}

	}


*/
/*event bind*/
/*
	insert a function pointer into the [events];

*/
