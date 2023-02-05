#pragma once

#include <cstring>
#include <string>
#include <vector>

#include <lvgl.h>

class UIWidget
{
public:
    UIWidget(std::vector<std::string> sensorInput);
    
    UIWidget(std::string sensorInput);

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

protected:
    std::vector<std::string> sensorInputs;
    
private:
    int id;
	
};