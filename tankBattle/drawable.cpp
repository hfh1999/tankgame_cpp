#include "drawable.h"
#include <fstream>
using std::ifstream;
Drawable::Drawable(std::string in_str) :is_managed(false), visualable(false), origin_point(COORD{ 0,0 }), relative_pos(std::vector<COORD>()), content(std::vector<TermChar>()),direct(DrawDirect::Up),old_direct(DrawDirect::Up)
{
	if (in_str == "look")//��ָ������lookͼ��ʱ��ִ��
	{
		TermChar ch(' ', TermChar::Foreground_Default, TermChar::Background_Yellow);//��ɫ�ո�
		for (SHORT i = 1; i <= 6; i++)//�����ĸ�����
		{
			for (SHORT j = 0; j < 4; j++)
			{
				relative_pos.push_back(COORD{ 1 + 4 * j,i });
				content.push_back(ch);
			}
		}
	}
	else {
		//��x0,y0;x1,y1;x2,y2;��ʽ��ͼ.
	}
}

void Drawable::turn_left()
{
	old_direct = direct;
	direct = DrawDirect::Left;
}

void Drawable::turn_right()
{
	old_direct = direct;
	direct = DrawDirect::Right;
}

void Drawable::turn_up()
{
	old_direct = direct;
	direct = DrawDirect::Up;
}

void Drawable::turn_down()
{
	old_direct = direct;
	direct = DrawDirect::Down;
}

void Drawable::move_left(SHORT step)
{
	old_point = origin_point;
	origin_point.X -= step;
}

void Drawable::move_right(SHORT step)
{
	old_point = origin_point;
	origin_point.X += step;
}

void Drawable::move_up(SHORT step)
{
	old_point = origin_point;
	origin_point.Y -= step;
}

void Drawable::move_down(SHORT step)
{
	old_point = origin_point;
	origin_point.Y += step;
}

void Drawable::move(COORD in_coord)
{
	old_point = origin_point;
	origin_point.Y = in_coord.Y;
	origin_point.X = in_coord.X;
}

void Drawable::set_visualable()
{
	visualable = true;
}

void Drawable::set_unvisualable()
{
	visualable = false;
}

const std::vector<COORD>& Drawable::ReturnPos()
{
	return relative_pos;
}

const std::vector<TermChar>& Drawable::Returncontent()
{
	return content;
}

COORD __resolve_coord_line(const std::string & instr)
{
	std::string left, right;
	auto pos = instr.find(',');  //���ŵ�λ��
	for (int count = 0; count < pos; count++)
		if(instr[count] != ' ' && instr[count] != '\t')//ȥ���հ��ַ�
			left.push_back(instr[count]);
	for (int count = pos + 1; count < instr.size(); count++)
		if(instr[count] != ' ' && instr[count] != '\t')
			right.push_back(instr[count]);

	return COORD{ (SHORT)std::stoi(left),(SHORT)std::stoi(right) }; // ǿ��ת������,��Ϊ������SHORT
}
std::shared_ptr<Drawable> get_drawable_from_file(const std::string & filename)
{

	ifstream draw_file(filename);
	bool status = true; // ��ʾһ�����Ѿ����꣬׼���ö���һ����

	std::string linebuf;
	std::vector<COORD> points;

	while (std::getline(draw_file, linebuf))
	{
		auto len_of_line = linebuf.size();
		if (status == true)
		{
			if (linebuf[0] == '[' && linebuf[len_of_line - 1] == ']')
			{
				status = false;
				//std::cout << linebuf << std::endl;
			}
			else
			{
				std::cout << "please check your draw file" << std::endl;// ����,Ӧ��Ϊ�׳�����
			}
		}
		else {
			if (linebuf[0] == '[' && linebuf[1] == '\\' and linebuf[len_of_line - 1] == ']')
			{
				// ���ﷵ��drawable��
				status == true;
				//std::cout << linebuf << std::endl;
			}
			else
			{
				// ����������,ȥ��ע��
				auto annotation_pos = linebuf.find("//");
				if (annotation_pos != std::string::npos)
				{
					linebuf.erase(annotation_pos, std::string::npos);
				}

				points.push_back(__resolve_coord_line(linebuf));
			}
		}
	}

	auto drawable_ptr = std::make_shared<Drawable>();
	TermChar ch(' ', TermChar::Foreground_Default, TermChar::Background_Yellow);//��ɫ�ո�
	for (auto point : points)
	{
		drawable_ptr->relative_pos.push_back(point);
		drawable_ptr->content.push_back(ch);
	}
	drawable_ptr->origin_point = COORD{ 5,5 }; // Ϊ�˹۲�Ч��
	drawable_ptr->old_point = COORD{ 5,5 };
	drawable_ptr->guid = generate_uuid();
	return drawable_ptr;
}
