#include "AdvLine.h"

LineStyle *LineStyle::instance = NULL;

AdvLine::AdvLine(
	lv_obj_t *parent,
	lv_point_t p1,
	lv_point_t p2,
	uint8_t lineWeight,
	lv_color_t lineColor,
	LineStyle::eLineType lineType)
{
	lv_style_t style = LineStyle::GetInstance()->GetStyle(lineType);
	lineObject = lv_line_create(parent);
	lv_point_t points[] = {{p1.x, p1.y},
						   {p2.x, p2.y}};
	lv_line_set_points(lineObject, points, 2);
	lv_style_set_line_width(&style, lineWeight);
	lv_style_set_line_color(&style, lineColor);
}