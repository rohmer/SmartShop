
/**
 * @file lv_line.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_sline.h"

/*********************
 *      DEFINES
 *********************/
#define MY_CLASS &lv_sline_class

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_sline_constructor(const lv_obj_class_t *class_p, lv_obj_t *obj);
static void lv_sline_destructor(const lv_obj_class_t *class_p, lv_obj_t *obj);
static void lv_sline_event(const lv_obj_class_t *class_p, lv_event_t *e);

/**********************
 *  STATIC VARIABLES
 **********************/
const lv_obj_class_t lv_sline_class = {
	.constructor_cb = lv_sline_constructor,
	.destructor_cb = lv_sline_destructor,
	.event_cb = lv_sline_event,
	.width_def = LV_SIZE_CONTENT,
	.height_def = LV_SIZE_CONTENT,
	.instance_size = sizeof(lv_sline_t),
	.base_class = &lv_obj_class};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t *lv_sline_create(lv_obj_t *parent)
{
	LV_LOG_INFO("begin");
	lv_obj_t *obj = lv_obj_class_create_obj(MY_CLASS, parent);
	lv_obj_class_init_obj(obj);
	return obj;
}

static void lv_sline_destructor(const lv_obj_class_t *class_p, lv_obj_t *obj)
{
	LV_UNUSED(class_p);
	lv_sline_t *line = (lv_sline_t *)obj;
	lv_mem_free(line->p1);
	lv_mem_free(line->p2);
	line->p1 = NULL;
	line->p2 = NULL;
}
/*=====================
 * Setter functions
 *====================*/
void lv_sline_set_y_invert(lv_obj_t *obj, bool en)
{
	LV_ASSERT_OBJ(obj, MY_CLASS);

	lv_sline_t *line = (lv_sline_t *)obj;
	if (line->y_inv == en)
		return;

	line->y_inv = en ? 1U : 0U;

	lv_obj_invalidate(obj);
}

void lv_sline_set_points(lv_obj_t *obj, lv_point_t p1, lv_point_t p2)
{
	LV_ASSERT_OBJ(obj, MY_CLASS);

	lv_sline_t *line = (lv_sline_t *)obj;
	memcpy((void *)line->p1, (void *)&p1, sizeof(lv_point_t));
	memcpy((void *)line->p2, (void *)&p2, sizeof(lv_point_t));
	lv_obj_refresh_self_size(obj);
	lv_obj_invalidate(obj);
}

/*=====================
 * Getter functions
 *====================*/

bool lv_sline_get_y_invert(const lv_obj_t *obj)
{
	LV_ASSERT_OBJ(obj, MY_CLASS);

	lv_sline_t *line = (lv_sline_t *)obj;

	return line->y_inv == 1U;
}

lv_point_t lv_sline_get_p1(const lv_obj_t *obj)
{
	LV_ASSERT_OBJ(obj, MY_CLASS);

	lv_sline_t *line = (lv_sline_t *)obj;

	return *line->p1;
}

lv_point_t lv_sline_get_p2(const lv_obj_t *obj)
{
	LV_ASSERT_OBJ(obj, MY_CLASS);

	lv_sline_t *line = (lv_sline_t *)obj;

	return *line->p2;
}
/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_sline_constructor(const lv_obj_class_t *class_p, lv_obj_t *obj)
{
	LV_UNUSED(class_p);
	LV_TRACE_OBJ_CREATE("begin");

	lv_sline_t *line = (lv_sline_t *)obj;
	line->p1 = (lv_point_t *)lv_mem_alloc(sizeof(lv_point_t));
	line->p2 = (lv_point_t *)lv_mem_alloc(sizeof(lv_point_t));
	line->y_inv = 0;

	lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);

	LV_TRACE_OBJ_CREATE("finished");
}

static void lv_sline_event(const lv_obj_class_t *class_p, lv_event_t *e)
{
	LV_UNUSED(class_p);

	lv_res_t res;

	/*Call the ancestor's event handler*/
	res = lv_obj_event_base(MY_CLASS, e);
	if (res != LV_RES_OK)
		return;

	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);

	if (code == LV_EVENT_REFR_EXT_DRAW_SIZE)
	{
		/*The corner of the skew lines is out of the intended area*/
		lv_coord_t line_width = lv_obj_get_style_line_width(obj, LV_PART_MAIN);
		lv_coord_t *s = (short *)lv_event_get_param(e);
		if (*s < line_width)
			*s = line_width;
	}
	else if (code == LV_EVENT_GET_SELF_SIZE)
	{
		lv_point_t *p = (lv_point_t *)lv_event_get_param(e);
		lv_sline_t *line = (lv_sline_t *)obj;

		lv_point_t *p1 = line->p1;
		lv_point_t *p2 = line->p2;
		lv_coord_t w = 0;
		lv_coord_t h = 0;

		uint16_t i;

		w = LV_MAX(line->p1->x, w);
		h = LV_MAX(line->p1->y, h);
		w = LV_MAX(line->p2->x, w);
		h = LV_MAX(line->p2->y, h);

		lv_coord_t line_width = lv_obj_get_style_line_width(obj, LV_PART_MAIN);
		w += line_width;
		h += line_width;
		p->x = w;
		p->y = h;
	}
	else if (code == LV_EVENT_DRAW_MAIN)
	{
		lv_sline_t *line = (lv_sline_t *)obj;
		lv_draw_ctx_t *draw_ctx = lv_event_get_draw_ctx(e);

		lv_area_t area;
		lv_obj_get_coords(obj, &area);
		lv_coord_t x_ofs = area.x1 - lv_obj_get_scroll_x(obj);
		lv_coord_t y_ofs = area.y1 - lv_obj_get_scroll_y(obj);
		lv_coord_t h = lv_obj_get_height(obj);

		lv_draw_line_dsc_t line_dsc;
		lv_draw_line_dsc_init(&line_dsc);
		lv_obj_init_draw_line_dsc(obj, LV_PART_MAIN, &line_dsc);

		/*Read all points and draw the lines*/

		lv_point_t p1;
		lv_point_t p2;
		p1.x = line->p1->x + x_ofs;
		p2.x = line->p2->x + x_ofs;

		if (line->y_inv == 0)
		{
			p1.y = line->p1->y + y_ofs;
			p2.y = line->p2->y + y_ofs;
		}
		else
		{
			p1.y = h - line->p1->y + y_ofs;
			p2.y = h - line->p2->y + y_ofs;
		}
		lv_draw_line(draw_ctx, &line_dsc, &p1, &p2);
		line_dsc.round_start = 0; /*Draw the rounding only on the end points after the first line*/
	}
}