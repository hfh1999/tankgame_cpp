#pragma once
#include <memory>
#include <vector>
#include "terminal.h"
#include "util.h"
class Drawable {//ͼ�εĻ���
private:
	const enum DrawDirect{Up,Right,Down,Left}; // ͼ�γ���Ķ���

	friend class TermioApp;
	friend  std::shared_ptr<Drawable> get_drawable_from_file(const std::string & filename);

	/* �������ڲ������� */

	std::string guid;// Ϊ�˱�ʶdrawable
	bool is_managed;// �Ƿ��Ѿ�����ʾ�ӹ�
	bool is_static;// ��̬���岻��Ҫ�ظ���Ⱦ
	bool visualable;//�ɼ���
	DrawDirect direct;//��ʾͼ�εĳ���
	DrawDirect old_direct; //�ϳ���
	COORD origin_point;//ԭ������
	COORD old_point;
	std::vector<COORD> relative_pos;//��ԭ��Ϊ���λ����ͼ
	std::vector<TermChar> content;//��Ӧλ�õķ���

	const std::vector<COORD>& ReturnPos();
	const std::vector<TermChar>& Returncontent();

public:
	Drawable(std::string in_str = "");//Ĭ�ϴ���һ���յ�,Ҳ������һ��look��ʶ(��Ҫָ��)
	Drawable(const Drawable & copy_src) :guid(generate_uuid()),is_managed(false),is_static(copy_src.is_static), visualable(copy_src.visualable),
		direct(copy_src.direct), old_direct(copy_src.old_direct), origin_point(copy_src.origin_point),
		old_point(copy_src.old_point),relative_pos(copy_src.relative_pos),content(copy_src.content)//copy structer
	{
	}
	Drawable& operator=(const Drawable &rhs) { //������ֵ����
		guid = generate_uuid();
		is_managed = false;
		is_static = rhs.is_static;
		visualable = rhs.visualable;
		direct = rhs.direct;
		old_direct = rhs.old_direct;
		origin_point = rhs.origin_point;
		old_point = rhs.old_point;
		relative_pos = rhs.relative_pos;
		content = rhs.content;
	}
	//DrawableObj();//����ͼ�������ļ�����һ��
	//void ReturnData();//һ��ͨ�õĽӿ�,�����ڲ������Ի�ͼ
	void turn_left();
	void turn_right();
	void turn_up();
	void turn_down();

	void move_left(SHORT step);
	void move_right(SHORT step);
	void move_up(SHORT step);
	void move_down(SHORT step);
	void move(COORD in_coord);//�����ƶ�
	void set_visualable(); // ��ͼ�οɼ�
	void set_unvisualable();// ��ͼ�β��ɼ�
	COORD ret_coord() { return origin_point; }
	std::string ret_guid() { return guid; }
	
	void set_static(bool flag) { is_static = flag; }
};

std::shared_ptr<Drawable> get_drawable_from_file(const std::string & filename);
