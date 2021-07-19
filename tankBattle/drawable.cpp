#include "drawable.h"
#include <fstream>
using std::ifstream;
Drawable::Drawable(std::string in_str) :is_managed(false), visualable(false), origin_point(COORD{ 0,0 }), relative_pos(std::vector<COORD>()), content(std::vector<TermChar>()),direct(DrawDirect::Up),old_direct(DrawDirect::Up)
{
	if (in_str == "look")//当指定生成look图形时才执行
	{
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
	auto pos = instr.find(',');  //逗号的位置
	for (int count = 0; count < pos; count++)
		if(instr[count] != ' ' && instr[count] != '\t')//去除空白字符
			left.push_back(instr[count]);
	for (int count = pos + 1; count < instr.size(); count++)
		if(instr[count] != ' ' && instr[count] != '\t')
			right.push_back(instr[count]);

	return COORD{ (SHORT)std::stoi(left),(SHORT)std::stoi(right) }; // 强制转换可行,因为总是用SHORT
}
std::shared_ptr<Drawable> get_drawable_from_file(const std::string & filename)
{

	ifstream draw_file(filename);
	bool status = true; // 表示一个段已经读完，准备好读下一个段

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
				std::cout << "please check your draw file" << std::endl;// 错误,应改为抛出错误
			}
		}
		else {
			if (linebuf[0] == '[' && linebuf[1] == '\\' and linebuf[len_of_line - 1] == ']')
			{
				// 这里返回drawable类
				status == true;
				//std::cout << linebuf << std::endl;
			}
			else
			{
				// 解析坐标行,去除注释
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
	TermChar ch(' ', TermChar::Foreground_Default, TermChar::Background_Yellow);//黄色空格
	for (auto point : points)
	{
		drawable_ptr->relative_pos.push_back(point);
		drawable_ptr->content.push_back(ch);
	}
	drawable_ptr->origin_point = COORD{ 5,5 }; // 为了观察效果
	drawable_ptr->old_point = COORD{ 5,5 };
	drawable_ptr->guid = generate_uuid();
	return drawable_ptr;
}
