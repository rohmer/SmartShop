#pragma once

#include <string>

struct TreeViewOptions
{
  public:	
	TreeViewOptions()
	{		
	}
	
	void SetSetbackSize(uint size = 8)
	{
		setbackSize = size;
	}

	uint GetSetbackSize()
	{
		return setbackSize;
	}
	
	
	// If there is no label, a window header will still be drawn
	void SetWindowHeader(bool WindowHeader)
	{
		windowHeader = WindowHeader;
	}

	bool GetWindowHeader()
	{
		return windowHeader;
	}

	bool DefaultToExpanded()
	{
		return defaultToExpanded;
	}

	void SetDefaultToExpanded(bool val)
	{
		defaultToExpanded = val;
	}

	lv_color_t GetAnchorColor()
	{
		return anchorColor;
	}

	void SetAnchorColor(lv_color_t val)
	{
		anchorColor = val;
	}

	lv_color_t GetItemTextColor()
	{
		return itemTextColor;
	}

	void SetItemTextColor(lv_color_t color)
	{
		itemTextColor = color;
	}

  private:
	uint setbackSize = 12;
	bool windowHeader = true;
	bool defaultToExpanded = true;
	lv_color_t anchorColor = lv_color_darken(lv_color_white(),16);
	lv_color_t itemTextColor = lv_color_white();
};