#pragma once

#include <sstream>
#include <string>
#include <vector>

#include "pigpio.h"

#include "DeviceBase.h"
#include "DeviceConfig.h"

class I2CDevice : public DeviceBase
{
public:
	enum eI2CBus
	{
		BUS_0=0,
		BUS_1=1
	};
	
	I2CDevice(std::string Name, std::string Description, eDeviceType DeviceType, unsigned short I2CAddress, eI2CBus I2CBus=eI2CBus::BUS_0, int PollingInterval=-1);
	I2CDevice(std::string Name, std::string Description, eDeviceType DeviceType, DeviceConfig config, unsigned short I2CAddress, eI2CBus I2CBus = eI2CBus::BUS_0, int PollingInterval=-1);
	~I2CDevice();
	
	unsigned short GetI2CAddress();
	bool WriteByte(unsigned value);
	int ReadByte();
	bool WriteByteData(unsigned i2cReg, unsigned value);
	int ReadByteData(unsigned i2cReg);
	bool WriteWordData(unsigned i2cReg, unsigned value);
	int ReadWordData(unsigned i2cReg);
	bool WriteBlockData(unsigned i2cReg, std::string value);
	std::string ReadBlockData(unsigned i2cReg);
	std::string ReadDevice(unsigned count);
	int WriteDevice(std::string data);
	std::string ReadI2CBlockData(unsigned i2cReg, unsigned short count);
	bool WriteI2CBlockData(unsigned i2cReg, std::string data);
	
	std::vector<uint8_t> ReadBytes(uint8_t size);
	
private:
	unsigned short i2cAddr;	
	eI2CBus i2cBus;
	bool busOpen = false;
	void openBus(eI2CBus bus, unsigned short address);
	int i2cHandle;
	void logError(int errNo, std::string msg);
};