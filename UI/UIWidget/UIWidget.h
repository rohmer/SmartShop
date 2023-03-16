#pragma once

#include <cstring>
#include <string>
#include <vector>

#include <lvgl.h>

#include "../../Logger/Logger.h"

class UIWidget
{
public:
    UIWidget(std::vector<std::string> sensorInput, std::string Name);  
    UIWidget(std::string sensorInput, std::string Name);
	virtual ~UIWidget() = default;
	
	static void event_cb(lv_event_t * e);
	
    bool ValidForInput(std::string sensor);

    virtual void Init()
    {
    }

	// It should be noted
	// Maximixed UI objects are deleted when their parent window is closed
	// Non-maximixed (ie. the widget icon) stay	
    virtual void Draw(lv_obj_t* parent, bool isMaximized, uint16_t width, uint16_t height, uint16_t x, uint16_t y)
    {
	    
    }

    int GetID()
    {
        return id;
    }

	std::vector<std::string> GetSensorInputs()
	{
		return sensorInputs;
	}
	
	std::string GetName()
	{
		return name;
	}
	
	typedef UIWidget * create_t();
	typedef void destroy_t(UIWidget *);
	
protected:
    std::vector<std::string> sensorInputs;
	lv_obj_t *baseObject, *minButton;
	Logger *log;
	
private:
    int id;
	std::string name;
	
};