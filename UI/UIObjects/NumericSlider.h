#pragma once

#include <sstream>
#include <string>
#include <vector>

#include <lvgl.h>

#include "Utils.h"

class NumericSlider
{
  public:
	NumericSlider(
		lv_obj_t *parent,
		uint x,
		uint y,
		uint width,
		uint height,
		int value=50,
		int maxValue = 100,
		int minValue = 0,
		lv_align_t numbersAlign = LV_ALIGN_OUT_BOTTOM_MID);

	NumericSlider(
		lv_obj_t *parent,
		uint x,
		uint y,
		uint width,
		uint height,
		std::string label,
		lv_align_t labelAlign = LV_ALIGN_OUT_TOP_MID,
		int value=50,
		int maxValue = 100,
		int minValue = 0,
		lv_align_t numbersAlign = LV_ALIGN_OUT_BOTTOM_MID);

	NumericSlider(
		lv_obj_t *parent,
		uint x,
		uint y,
		uint width,
		uint height,
		int leftValue = 20,
		int rightValue = 80,
		int maxValue = 100,
		int minValue = 0,
		lv_align_t numbersAlign = LV_ALIGN_OUT_BOTTOM_MID);

	NumericSlider(
		lv_obj_t *parent,
		uint x,
		uint y,
		uint width,
		uint height,
		std::string label,
		lv_align_t labelAlign = LV_ALIGN_OUT_TOP_MID,
		int leftValue = 20,
		int rightValue = 80,
		int maxValue = 100,
		int minValue = 0,
		lv_align_t numbersAlign = LV_ALIGN_OUT_BOTTOM_MID);
	
	~NumericSlider();
	int GetValue();
	int GetMaxValue();
	int GetMinValue();
	int GetStepValue();

	int GetLeftValue();
	int GetRightValue();
	
	lv_align_t GetValueAlign();
	lv_obj_t *GetValueObject();
	lv_obj_t *GetSliderObject();

  private:
	lv_obj_t *sliderObj=NULL, *labelObj=NULL, *valueObj=NULL;

	lv_align_t valueAlign;
	
	static void slider_event_cb(lv_event_t *e);
	static void slider_drawer_event_cb(lv_event_t *e);
	bool isDrawer = false;
};