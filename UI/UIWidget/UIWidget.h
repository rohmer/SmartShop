#pragma once

#include <cstring>
#include <string>
#include <vector>

#include <lvgl.h>

class UIWidget
{
public:
    UIWidget(std::vector<std::string> sensorInput, std::string Name);  
    UIWidget(std::string sensorInput, std::string Name);
	virtual ~UIWidget() = default;
	
    bool ValidForInput(std::string sensor);

    virtual void Init()
    {
    }

    virtual void Draw(lv_obj_t* parent, uint16_t width, uint16_t height, uint16_t x, uint16_t y)
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
	lv_obj_t *baseObject;
private:
    int id;
	std::string name;
	
};