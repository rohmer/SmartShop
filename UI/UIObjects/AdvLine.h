#pragma once

#include <lvgl.h>

struct LineStyle
{
  public:
	enum eLineType
	{
		SOLID,
		DASHED,
		DOTTED
	};

	static LineStyle *GetInstance()
	{
		if (instance == NULL)
			instance = new LineStyle();
		return instance;
	}

	lv_style_t GetStyle(eLineType lineType)
	{
		switch (lineType)
		{
			case eLineType::DASHED:
				return dashed;
			case eLineType::DOTTED:
				return dotted;
			case eLineType::SOLID:
				return solid;
		}
		return solid;
	}

  private:
	static  LineStyle *instance;
	lv_style_t dotted, dashed, solid;

	LineStyle()
	{
		lv_style_init(&solid);
		lv_style_set_line_rounded(&solid, true);

		lv_style_init(&dashed);
		lv_style_set_line_rounded(&dashed, true);
		lv_style_set_line_dash_gap(&dashed, 2);
		lv_style_set_line_dash_width(&dashed, 3);

		lv_style_init(&dotted);
		lv_style_set_line_rounded(&dotted, true);
		lv_style_set_line_dash_gap(&dotted, 2);
		lv_style_set_line_dash_width(&dotted, 1);
	}
}; 

struct AdvLine
{
  public:
	AdvLine(
		lv_obj_t *parent,
		lv_point_t p1,
		lv_point_t p2,
		uint8_t lineWeight = 2,
		lv_color_t lineColor = lv_color_hex(0xFFFFFF),
		LineStyle::eLineType lineType=LineStyle::DASHED);

  private:
	lv_obj_t *lineObject;
};