#pragma once
/**
 * @file lv_line.h
 *
 */
#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <lvgl.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of line*/
typedef struct
{
	lv_obj_t obj;
	lv_point_t *p1, *p2;
	uint8_t y_inv : 1;			   /**< 1: y == 0 will be on the bottom*/
} lv_sline_t;

extern const lv_obj_class_t lv_sline_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a line object
 * @param parent pointer to an object, it will be the parent of the new line
 * @return pointer to the created line
 */
lv_obj_t *lv_sline_create(lv_obj_t *parent);

/*=====================
 * Setter functions
 *====================*/

void lv_sline_set_points(lv_obj_t *obj, lv_point_t p1, lv_point_t p2);

/**
 * Enable (or disable) the y coordinate inversion.
 * If enabled then y will be subtracted from the height of the object,
 * therefore the y = 0 coordinate will be on the bottom.
 * @param obj       pointer to a line object
 * @param en        true: enable the y inversion, false:disable the y inversion
 */
void lv_sline_set_y_invert(lv_obj_t *obj, bool en);

/*=====================
 * Getter functions
 *====================*/

/**
 * Get the y inversion attribute
 * @param obj       pointer to a line object
 * @return          true: y inversion is enabled, false: disabled
 */
bool lv_sline_get_y_invert(const lv_obj_t *obj);

lv_point_t lv_sline_get_p1(const lv_obj_t *obj);
lv_point_t lv_sline_get_p2(const lv_obj_t *obj);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

