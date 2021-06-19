#pragma once
#include <memory>
#include <vector>
#include "terminal.h"
class Drawable {//ͼ�εĻ���
private:
	const enum DrawDirect{Left,Right,Up,Down}; // ͼ�γ���Ķ���

	bool is_managed;// �Ƿ��Ѿ�����ʾ�ӹ�
	friend class TermioApp;
	friend  std::shared_ptr<Drawable> get_drawable_from_file(std::string filename);

	/* �������ڲ������� */

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
	void set_visualable(); // ��ͼ�οɼ�
	void set_unvisualable();// ��ͼ�β��ɼ�
	
};
std::shared_ptr<Drawable> get_drawable_from_file(std::string filename);
