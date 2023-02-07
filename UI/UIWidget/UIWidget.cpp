#include "UIWidget.h"

UIWidget::UIWidget(std::vector<std::string> sensorInput, std::string Name) :
	name(Name)
{
    for (std::vector<std::string>::iterator it = sensorInput.begin(); it != sensorInput.end(); ++it)
        sensorInputs.push_back(*it);
	id = std::rand();
}

UIWidget::UIWidget(std::string sensorInput, std::string Name) :
	name(Name)
{
    sensorInputs.push_back(sensorInput);
}

bool UIWidget::ValidForInput(std::string sensor)
{
    for (int i = 0; i < sensorInputs.size(); i++)
    {
        if (std::strcmp(sensorInputs[i].c_str(), sensor.c_str()) == 0)
            return true;
        if (std::strcmp(sensorInputs[i].c_str(), "ALL") == 0)
            return true;
    }
    return false;
}

