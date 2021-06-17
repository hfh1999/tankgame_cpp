/*��teminal������input������*/
//��Ҫһ���¼�ѭ������event loop��������event
#include "terminal.h"
#include <thread>
#include <vector>
#include <memory>
using std::shared_ptr;
class Drawable {//ͼ�εĻ���
private:
	bool is_managed;// �Ƿ��Ѿ�����ʾ�ӹ�
	friend class TermioApp;

	/* �������ڲ������� */

	bool visualable;//�ɼ���
	COORD origin_point;//ԭ������
	COORD old_point;
	std::vector<COORD> relative_pos;//��ԭ��Ϊ���λ����ͼ
	std::vector<TermChar> content;//��Ӧλ�õķ���

	const std::vector<COORD>& ReturnPos();
	const std::vector<TermChar>& Returncontent();
public:
	Drawable(std::string in_str = "");//Ĭ�ϴ���һ���յ�,Ҳ������һ��look��ʶ(��Ҫָ��)
	//DrawableObj();//����ͼ�������ļ�����һ��
	//void ReturnData();//һ��ͨ�õĽӿ�,�����ڲ������Ի�ͼ
	void move_left(SHORT step);
	void move_right(SHORT step);
	void move_up(SHORT step);
	void move_down(SHORT step);
	void set_visualable();


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

	bool addDrawable(shared_ptr<Drawable> in_obj, bool is_visuable = true);//����Drawable object
	bool removeDrawable(std::string id);//���涨id�Ķ�����б����Ƴ�
	bool setVisuable(std::string id, bool visuable_value = true);//���ö���Ŀɼ���
	
private:
	HANDLE termapp_in;//�����ʶ��
	std::thread event_loop;
	bool loop_flag = true;//�Ƿ�ֹͣ�¼�ѭ��
	std::vector<shared_ptr<Drawable>> obj_list;//app�Ѿ������Drawable object���б�

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

